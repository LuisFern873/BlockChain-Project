# include <iostream>
# include "b+tree.h"

int main()
{
  BPTree node;
  node.insert(5);
  node.insert(15);
  node.insert(25);
  node.insert(35);
  node.insert(45);
  node.insert(55);
  node.insert(40);
  node.insert(30);
  node.insert(20);
  node.insert(90);
  node.insert(100);
  // node.display(node.getRoot());

  node.displayPretty();

  node.remove(15);

    node.remove(35);

  node.search(15);

  node.displayPretty();

    // for (int i = 0; i < 5; ++i) {
    //     tree->insert(rand() % 100);
    // }
        

    // tree->displayPretty();
    return 0;
}