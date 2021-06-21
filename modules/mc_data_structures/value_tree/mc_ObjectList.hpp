#include <utility>

#ifndef MC_JUCE_BUNDLE_VALUE_TREE_OBJECT_LIST_HPP
#define MC_JUCE_BUNDLE_VALUE_TREE_OBJECT_LIST_HPP

namespace mc
{

template<typename ObjectType, typename CriticalSectionType = juce::DummyCriticalSection>
class ValueTreeObjectList : public juce::ValueTree::Listener
{
public:
    explicit ValueTreeObjectList(juce::ValueTree parentTree) : parent_(std::move(parentTree))
    {
        parent_.addListener(this);
    }

    ~ValueTreeObjectList() override  // NOLINT
    {
        // must call freeObjects() in the subclass destructor!
        jassert(objects_.empty());
    }

    [[nodiscard]] virtual auto isSuitableType(juce::ValueTree const&) const -> bool = 0;
    virtual auto makeObject(juce::ValueTree const&) -> ObjectType*                  = 0;
    virtual void deleteObject(ObjectType*)                                          = 0;

    virtual void objectAdded(ObjectType*)   = 0;
    virtual void objectRemoved(ObjectType*) = 0;
    virtual void objectOrderChanged()       = 0;

    /**
     * @brief Call in the sub-class when being created.
     */
    void rebuildObjects()
    {
        jassert(objects_.empty());  // must only call this method once at construction

        for (const auto& v : parent_)
        {
            if (isSuitableType(v))
            {
                if (auto* newObject = makeObject(v); newObject != nullptr) { objects_.push_back(newObject); }
            }
        }
    }

    /**
     * @brief Call in the sub-class when being destroyed
     */
    void freeObjects()
    {
        parent_.removeListener(this);
        deleteAllObjects();
    }

    [[nodiscard]] auto getObjects() -> std::vector<ObjectType*>& { return objects_; }
    [[nodiscard]] auto getObjects() const -> std::vector<ObjectType*> const& { return objects_; }
    [[nodiscard]] auto getValueTree() noexcept -> juce::ValueTree& { return parent_; }

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

    [[nodiscard]] auto indexOf(juce::ValueTree const& v) const noexcept -> int
    {
        for (std::size_t i = 0; i < objects_.size(); ++i)
        {
            if (objects_[i]->getValueTree() == v) { return static_cast<int>(i); }
        }

        return -1;
    }

private:
    void valueTreeChildAdded(juce::ValueTree& /*parent*/, juce::ValueTree& tree) override
    {
        if (isChildTree(tree))
        {
            [[maybe_unused]] auto const index = parent_.indexOf(tree);
            jassert(index >= 0);

            if (ObjectType* newObject = makeObject(tree); newObject != nullptr)
            {
                {
                    ScopedLockType lock(objectsMutex_);
                    objects_.push_back(newObject);
                    if (index != parent_.getNumChildren() - 1) { sortArray(); }
                }

                objectAdded(newObject);
            }
            else
            {
                jassertfalse;
            }
        }
    }

    void valueTreeChildRemoved(juce::ValueTree& exParent, juce::ValueTree& tree, int /*id*/) override
    {
        if (parent_ == exParent && isSuitableType(tree))
        {
            auto const oldIndex = indexOf(tree);

            if (oldIndex >= 0)
            {
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
        if (tree == parent_)
        {
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
    }  // may need to add handling if this is hit

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ValueTreeObjectList)  // NOLINT
};

}  // namespace mc

#endif  // MC_JUCE_BUNDLE_VALUE_TREE_OBJECT_LIST_HPP
