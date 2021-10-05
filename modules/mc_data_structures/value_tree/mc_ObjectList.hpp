#ifndef MC_JUCE_BUNDLE_VALUE_TREE_OBJECT_LIST_HPP
#define MC_JUCE_BUNDLE_VALUE_TREE_OBJECT_LIST_HPP

namespace mc {

template <typename ObjectType, typename CriticalSectionType = juce::DummyCriticalSection>
struct ValueTreeObjectList : public juce::ValueTree::Listener {
    explicit ValueTreeObjectList(juce::ValueTree parentTree)
        : parent_(std::move(parentTree))
    {
        parent_.addListener(this);
    }

    ~ValueTreeObjectList() override // NOLINT
    {
        // must call freeObjects() in the subclass destructor!
        jassert(objects_.empty());
    }

    MC_NODISCARD virtual auto isSuitableType(juce::ValueTree const&) const -> bool = 0;
    virtual auto makeObject(juce::ValueTree const&) -> ObjectType*                 = 0;
    virtual void deleteObject(ObjectType*)                                         = 0;

    virtual void objectAdded(ObjectType*)   = 0;
    virtual void objectRemoved(ObjectType*) = 0;
    virtual void objectOrderChanged()       = 0;

    /// \brief Call in the sub-class when being created.
    void rebuildObjects()
    {
        jassert(objects_.empty()); // must only call this method once at construction

        for (const auto& v : parent_) {
            if (isSuitableType(v)) {
                auto* newObject = makeObject(v);
                if (newObject != nullptr) {
                    objects_.push_back(newObject);
                }
            }
        }
    }

    /// \brief Call in the sub-class when being destroyed
    void freeObjects()
    {
        parent_.removeListener(this);
        deleteAllObjects();
    }

    MC_NODISCARD auto getObjects() -> std::vector<ObjectType*>& { return objects_; }
    MC_NODISCARD auto getObjects() const -> std::vector<ObjectType*> const& { return objects_; }
    MC_NODISCARD auto getValueTree() noexcept -> juce::ValueTree& { return parent_; }

protected:
    using ScopedLockType = typename CriticalSectionType::ScopedLockType;
    CriticalSectionType objectsMutex_;
    std::vector<ObjectType*> objects_ {};
    juce::ValueTree parent_ {};

    void deleteAllObjects()
    {
        ScopedLockType lock(objectsMutex_);
        std::for_each(std::begin(objects_), std::end(objects_), [this](auto* obj) { deleteObject(obj); });
        objects_.clear();
    }

    auto isChildTree(juce::ValueTree& v) const -> bool { return isSuitableType(v) && v.getParent() == parent_; }

    MC_NODISCARD auto indexOf(juce::ValueTree const& v) const noexcept -> int
    {
        for (std::size_t i = 0; i < objects_.size(); ++i) {
            if (objects_[i]->getValueTree() == v) {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

private:
    void valueTreeChildAdded(juce::ValueTree& /*parent*/, juce::ValueTree& tree) override
    {
        if (isChildTree(tree)) {
            auto const index = parent_.indexOf(tree);
            (void)index;
            jassert(index >= 0);

            ObjectType* newObject = makeObject(tree);
            if (newObject != nullptr) {
                {
                    ScopedLockType lock(objectsMutex_);
                    objects_.push_back(newObject);
                    if (index != parent_.getNumChildren() - 1) {
                        sortArray();
                    }
                }

                objectAdded(newObject);
            } else {
                jassertfalse;
            }
        }
    }

    void valueTreeChildRemoved(juce::ValueTree& exParent, juce::ValueTree& tree, int /*id*/) override
    {
        if (parent_ == exParent && isSuitableType(tree)) {
            auto const oldIndex = indexOf(tree);

            if (oldIndex >= 0) {
                ObjectType* o;

                {
                    ScopedLockType const lock(objectsMutex_);
                    o = objects_.back();
                    objects_.pop_back();
                }

                objectRemoved(o);
                deleteObject(o);
            }
        }
    }

    void valueTreeChildOrderChanged(juce::ValueTree& tree, int /*oldIndex*/, int /*newIndex*/) override
    {
        if (tree == parent_) {
            {
                ScopedLockType const lock(objectsMutex_);
                sortArray();
            }

            objectOrderChanged();
        }
    }

    void valueTreePropertyChanged(juce::ValueTree& /*treeWhosePropertyHasChanged*/,
        juce::Identifier const& /*property*/) override
    {
    }
    void valueTreeParentChanged(juce::ValueTree& /*treeWhoseParentHasChanged*/) override { }

    void valueTreeRedirected(juce::ValueTree& /*treeWhichHasBeenChanged*/) override
    {
        jassertfalse;
    } // may need to add handling if this is hit

    void sortArray()
    {
        auto compare = [this](auto* lhs, auto* rhs) { return compareElements(lhs, rhs); };
        std::sort(std::begin(objects_), std::end(objects_), compare);
    }

    auto compareElements(ObjectType* first, ObjectType* second) const -> int
    {
        auto const index1 = parent_.indexOf(first->getValueTree());
        auto const index2 = parent_.indexOf(second->getValueTree());
        return index1 - index2;
    }

    JUCE_LEAK_DETECTOR(ValueTreeObjectList) // NOLINT
};

template <typename ObjectType, typename CriticalSectionType = juce::DummyCriticalSection>
struct ValueTreeObjectListV2 : juce::ValueTree::Listener {
    explicit ValueTreeObjectListV2(juce::ValueTree parentTree)
        : parent(std::move(parentTree))
    {
        parent.addListener(this);
    }

    ~ValueTreeObjectListV2() override // NOLINT
    {
        jassert(objects.isEmpty()); // must call freeObjects() in the subclass destructor!
    }

    MC_NODISCARD inline auto size() const -> int { return objects.size(); }
    MC_NODISCARD inline auto isEmpty() const noexcept -> bool { return size() == 0; }
    auto operator[](int idx) const -> ObjectType* { return objects[idx]; }
    auto at(int idx) -> ObjectType* { return objects[idx]; }
    auto begin() -> ObjectType** { return objects.begin(); }
    auto begin() const -> ObjectType* const* { return objects.begin(); }
    auto end() -> ObjectType** { return objects.end(); }
    auto end() const -> ObjectType* const* { return objects.end(); }

    // call in the sub-class when being created
    void rebuildObjects()
    {
        jassert(objects.isEmpty()); // must only call this method once at construction

        for (const auto& v : parent) {
            if (isSuitableType(v)) {
                if (auto newObject = createNewObject(v)) {
                    objects.add(newObject);
                }
            }
        }
    }

    // call in the sub-class when being destroyed
    void freeObjects()
    {
        parent.removeListener(this);
        deleteAllObjects();
    }

    //==============================================================================
    MC_NODISCARD virtual auto isSuitableType(juce::ValueTree const&) const -> bool = 0;
    virtual auto createNewObject(juce::ValueTree const&) -> ObjectType*            = 0;
    virtual void deleteObject(ObjectType*)                                         = 0;

    virtual void newObjectAdded(ObjectType*) = 0;
    virtual void objectRemoved(ObjectType*)  = 0;
    virtual void objectOrderChanged()        = 0;

    //==============================================================================
    void valueTreeChildAdded(juce::ValueTree& /*parentTree*/, juce::ValueTree& tree) override
    {
        if (isChildTree(tree)) {
            auto index = parent.indexOf(tree);
            juce::ignoreUnused(index);
            jassert(index >= 0);

            if (auto* newObject = createNewObject(tree)) {
                {
                    const ScopedLockType sl(arrayLock);

                    if (index == parent.getNumChildren() - 1) {
                        objects.add(newObject);
                    } else {
                        objects.addSorted(*this, newObject);
                    }
                }

                newObjectAdded(newObject);
            } else {
                jassertfalse;
            }
        }
    }

    void valueTreeChildRemoved(juce::ValueTree& exParent, juce::ValueTree& tree,
        int /*indexFromWhichChildWasRemoved*/) override
    {
        if (parent == exParent && isSuitableType(tree)) {
            auto oldIndex = indexOf(tree);

            if (oldIndex >= 0) {
                ObjectType* o;

                {
                    const ScopedLockType sl(arrayLock);
                    o = objects.removeAndReturn(oldIndex);
                }

                objectRemoved(o);
                deleteObject(o);
            }
        }
    }

    void valueTreeChildOrderChanged(juce::ValueTree& tree, int /*oldIndex*/, int /*newIndex*/) override
    {
        if (tree == parent) {
            {
                const ScopedLockType sl(arrayLock);
                sortArray();
            }

            objectOrderChanged();
        }
    }

    void valueTreePropertyChanged(juce::ValueTree& /*treeWhosePropertyHasChanged*/,
        const juce::Identifier& /*property*/) override
    {
    }
    void valueTreeParentChanged(juce::ValueTree& /*treeWhoseParentHasChanged*/) override { }

    void valueTreeRedirected(juce::ValueTree& /*treeWhichHasBeenChanged*/) override
    {
        jassertfalse;
    } // may need to add handling if this is hit

    juce::Array<ObjectType*> objects;
    CriticalSectionType arrayLock;
    using ScopedLockType = typename CriticalSectionType::ScopedLockType;

protected:
    juce::ValueTree parent;

    void deleteAllObjects()
    {
        const ScopedLockType sl(arrayLock);

        while (objects.size() > 0) {
            deleteObject(objects.removeAndReturn(objects.size() - 1));
        }
    }

    auto isChildTree(juce::ValueTree& v) const -> bool { return isSuitableType(v) && v.getParent() == parent; }

    MC_NODISCARD auto indexOf(juce::ValueTree const& v) const noexcept -> int
    {
        for (int i = 0; i < objects.size(); ++i) {
            if (objects.getUnchecked(i)->state == v) {
                return i;
            }
        }

        return -1;
    }

    void sortArray() { objects.sort(*this); }

public:
    auto compareElements(ObjectType* first, ObjectType* second) const -> int
    {
        int index1 = parent.indexOf(first->state);
        int index2 = parent.indexOf(second->state);
        return index1 - index2;
    }

    JUCE_LEAK_DETECTOR(ValueTreeObjectListV2) // NOLINT
};

} // namespace mc

#endif // MC_JUCE_BUNDLE_VALUE_TREE_OBJECT_LIST_HPP
