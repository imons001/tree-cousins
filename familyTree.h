#ifndef FAMILYTREE_H
#define FAMILYTREE_H

#include <vector>

class FamilyTree
{
    int identifier;
    FamilyTree *parent;
    std::vector<FamilyTree *> children;

public:
    typedef std::vector<FamilyTree *>::iterator iterator;
    typedef std::vector<FamilyTree *>::const_iterator const_iterator;

    /**
     * @brief Construct a new Family Tree object
     * 
     * @param id identifier of this node
     * @param theParent pointer to the parent of this node, null if this will be the root.
     */
    FamilyTree(int id, FamilyTree *theParent = nullptr);
    ~FamilyTree();

    /**
     * @brief Get the identifier for this node
     * 
     * @return int 
     */
    int getIdentifier() const {return identifier;}

    /**
     * @brief Get the parent of this node
     * 
     * @return the parent, or null if this is the root
     */
    FamilyTree *getParent() {return parent;}
    const FamilyTree *getParent() const {return parent;}

    /**
     * @brief the number of cousins of this node
     * 
     * @return the number of cousins
     */
    int numberOfCousins() const;

    /**
     * @brief Find a node
     * 
     * @param identifier the identifier to search for
     * @return the descendent of this node (or this node itself) matching the identifier, or
     *         null if no such matching node exists
     */
    const FamilyTree *find(int identifier) const;
    FamilyTree *find(int identifier);

    /**
     * @brief Iterator access (to children of this node)
     * 
     * @return iterator 
     */
    iterator begin() {return children.begin();}
    const_iterator begin() const {return children.begin();}
    iterator end() {return children.end();}
    const_iterator end() const {return children.end();}

private:

    // Because these are private, they cannot be called
    FamilyTree(const FamilyTree &) {}
    void operator=(const FamilyTree &) {}
};

#endif