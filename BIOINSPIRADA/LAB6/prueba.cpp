// find_if example
#include <iostream>     // std::cout
#include <algorithm>    // std::find_if
#include <vector>       // std::vector

bool IsOdd (int i) {
  return ((i%2)==1);
}

int main () {
  std::vector<int> myvector;

  myvector.push_back(10);
  myvector.push_back(20);
  myvector.push_back(40);
  myvector.push_back(55);

  std::vector<int>::iterator it = std::find_if (myvector.begin(), myvector.end(), IsOdd);
  if(it==myvector.end()){
  	std::cout<<"no esta \n";
  }else{
	auto index=std::distance(myvector.begin(),it);
	std::cout << "The first odd position is " << index << '\n';
  	std::cout << "The first odd value is " << *it << '\n';
  }
  return 0;
}
