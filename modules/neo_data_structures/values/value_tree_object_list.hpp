#pragma once

namespace neo {

template <typename T>
struct ValueTreeObjectList : juce::ValueTree::Listener {
    explicit ValueTreeObjectList(juce::ValueTree parentTree);
    ~ValueTreeObjectList() override;

    ValueTreeObjectList(ValueTreeObjectList const&) = delete;
    ValueTreeObjectList(ValueTreeObjectList&&)      = delete;

    auto operator=(ValueTreeObjectList const&) -> ValueTreeObjectList& = delete;
    auto operator=(ValueTreeObjectList&&) -> ValueTreeObjectList&      = delete;

    [[nodiscard]] virtual auto isSuitableType(juce::ValueTree const&) const -> bool = 0;
    [[nodiscard]] virtual auto createNewObject(juce::ValueTree const&) -> T*        = 0;
    virtual auto deleteObject(T*) -> void                                           = 0;
    virtual auto newObjectAdded(T*) -> void                                         = 0;
    virtual auto objectRemoved(T*) -> void                                          = 0;
    virtual auto objectOrderChanged() -> void                                       = 0;

    [[nodiscard]] auto empty() const noexcept { return isEmpty(objects); }

    [[nodiscard]] auto size() const noexcept { return objects.size(); }

    [[nodiscard]] auto begin() noexcept { return objects.begin(); }

    [[nodiscard]] auto begin() const noexcept { return objects.begin(); }

    [[nodiscard]] auto end() noexcept { return objects.end(); }

    [[nodiscard]] auto end() const noexcept { return objects.end(); }

    [[nodiscard]] auto cbegin() const noexcept { return objects.cbegin(); }

    [[nodiscard]] auto cend() const noexcept { return objects.cend(); }

    [[nodiscard]] auto operator[](size_t index) noexcept -> T& { return *objects[static_cast<int>(index)]; }

    [[nodiscard]] auto operator[](size_t index) const noexcept -> T const& { return *objects[static_cast<int>(index)]; }

    auto rebuildObjects() -> void;
    auto freeObjects() -> void;

    auto valueTreeChildAdded(juce::ValueTree& parentTree, juce::ValueTree& tree) -> void override;
    auto valueTreeChildRemoved(juce::ValueTree& exParent, juce::ValueTree& tree, int index) -> void override;
    auto valueTreeChildOrderChanged(juce::ValueTree& tree, int oldIndex, int newIndex) -> void override;
    auto valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) -> void override;
    auto valueTreeParentChanged(juce::ValueTree& tree) -> void override;
    auto valueTreeRedirected(juce::ValueTree& tree) -> void override;

    auto compareElements(T* first, T* second) const -> int;

    juce::Array<T*> objects;

protected:
    juce::ValueTree parent;

    auto deleteAllObjects() -> void;
    auto isChildTree(juce::ValueTree& v) const -> bool;
    [[nodiscard]] auto indexOf(juce::ValueTree const& v) const noexcept -> int;
    auto sortArray() -> void;
};

template <typename T>
ValueTreeObjectList<T>::ValueTreeObjectList(juce::ValueTree parentTree) : parent(std::move(parentTree))
{
    parent.addListener(this);
}

template <typename T>
ValueTreeObjectList<T>::~ValueTreeObjectList()
{
    // must call freeObjects() in the subclass destructor!
    jassert(size() == 0);
}

// call in the sub-class when being created
template <typename T>
void ValueTreeObjectList<T>::rebuildObjects()
{
    // must only call this method once at construction
    jassert(size() == 0);

    for (auto const& v : parent) {
        if (isSuitableType(v)) {
            if (T* newObject = createNewObject(v)) {
                objects.add(newObject);
                newObjectAdded(newObject);
            }
        }
    }
}

// call in the sub-class when being destroyed
template <typename T>
void ValueTreeObjectList<T>::freeObjects()
{
    parent.removeListener(this);
    deleteAllObjects();
}

template <typename T>
void ValueTreeObjectList<T>::valueTreeChildAdded(juce::ValueTree& /*parentTree*/, juce::ValueTree& tree)
{
    if (!isChildTree(tree)) { return; }

    int const index = parent.indexOf(tree);
    jassert(index >= 0);

    if (auto* obj = createNewObject(tree); obj != nullptr) {
        if (index == parent.getNumChildren() - 1) {
            objects.add(obj);
        } else {
            objects.addSorted(*this, obj);
        }

        newObjectAdded(obj);
    } else {
        jassertfalse;
    }
}

template <typename T>
void ValueTreeObjectList<T>::valueTreeChildRemoved(juce::ValueTree& exParent, juce::ValueTree& tree, int /*index*/)
{
    if (parent == exParent && isSuitableType(tree)) {
        int const oldIndex = indexOf(tree);

        if (oldIndex >= 0) {
            T* o = nullptr;
            o    = objects.removeAndReturn(oldIndex);

            objectRemoved(o);
            deleteObject(o);
        }
    }
}

template <typename T>
void ValueTreeObjectList<T>::valueTreeChildOrderChanged(juce::ValueTree& tree, int /*oldIndex*/, int /*newIndex*/)
{
    if (tree == parent) {
        sortArray();
        objectOrderChanged();
    }
}

template <typename T>
void ValueTreeObjectList<T>::valueTreePropertyChanged(juce::ValueTree& /*tree*/, juce::Identifier const& /*property*/)
{
}

template <typename T>
void ValueTreeObjectList<T>::valueTreeParentChanged(juce::ValueTree& /*tree*/)
{
}

template <typename T>
void ValueTreeObjectList<T>::valueTreeRedirected(juce::ValueTree& /*tree*/)
{
    // may need to add handling if this is hit
    jassertfalse;
}

template <typename T>
void ValueTreeObjectList<T>::deleteAllObjects()
{
    while (size() > 0) {
        auto* obj = objects.removeAndReturn(size() - 1);
        objectRemoved(obj);
        deleteObject(obj);
    }
}

template <typename T>
auto ValueTreeObjectList<T>::isChildTree(juce::ValueTree& v) const -> bool
{
    return isSuitableType(v) && v.getParent() == parent;
}

template <typename T>
auto ValueTreeObjectList<T>::indexOf(juce::ValueTree const& v) const noexcept -> int
{
    for (int i = 0; i < size(); ++i) {
        if (objects.getUnchecked(i)->valueTree() == v) { return i; }
    }

    return -1;
}

template <typename T>
void ValueTreeObjectList<T>::sortArray()
{
    objects.sort(*this);
}

template <typename T>
auto ValueTreeObjectList<T>::compareElements(T* first, T* second) const -> int
{
    auto const index1 = parent.indexOf(first->valueTree());
    auto const index2 = parent.indexOf(second->valueTree());
    return index1 - index2;
}

} // namespace neo
