// Alfredo Morales
// 
// We created  a class call Chain. It is just a series of items (an array). 
// This chain can have any size. The purpose of this assignment was to build the class without using any STL.
// We constructed Weiss's "big five", the destructor, copy constructor, copy assignment operator, move constructor and move assignment operation
// We also learned about overloading operators to help our executions less complicated and hectic.

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_

#include <iostream>
#include <cstddef>
#include <array>
#include <string>
#include <sstream>


namespace teaching_project {

template<typename Object>

class Chain {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  // and you will provide an implementation.

  // Zero-parameter constructor.
  Chain(){
    size_ = 0;
    array_ = nullptr; 
  }

  // Copy-constructor.
  Chain(const Chain &rhs){	// This constructor is simple
							// We are simply copying the data from certain variales
    size_ = rhs.size_;		// into new ones.		
    array_ = new Object[size_]; 
    for(unsigned int i = 0;i < rhs.size_;i++){
      array_[i] = rhs.array_[i]; 
    }

  }

  // Copy-assignment. 
  
  Chain& operator=(const Chain &rhs){

    Chain copy = rhs; 
    std::swap(*this, copy);
    return *this;
  }

  // Move-constructor. 
  Chain(Chain&& rhs) : size_(0), array_(nullptr){

	  size_ = rhs.size_;
	  array_ = rhs.array_;

	  //reset rhs
	  rhs.size_ = 0;
	  rhs.array_ = nullptr;	  
  }


  // Move-assignment.
  Chain& operator=(Chain&& rhs) {
	  if (this != &rhs)
	  {
		  // release the current object's resources
		  delete[] array_;
		  size_ = 0;


		  // pilfer other's resource
		  size_ = rhs.size_;
		  array_ = rhs.array_;

		  // reset other
		  rhs.size_ = 0;
		  rhs.array_ = nullptr;
	  }
	  return *this;

  }

  ~Chain() {

    delete []array_; 
    size_ = 0;
    
    // Provide destructor.
  }

  /*****************************        End of big-five.     *******************************/

  // One parameter constructor.
  Chain(const Object& item) {
    size_ = 1; 
    array_ = new Object[1];
    array_[0] = item;
  }

  // Read a chain from standard input.
  void ReadChain() {

	  std::string line;
	  getline(std::cin, line);
	  line.erase(0, 1);
	  line.pop_back();

	  std::stringstream ss(line);

	  ss >> size_;
	  Object var2;
	  array_ = new Object[size_];
	  char ch = ss.get();
	  for (unsigned int i = 0; i < size_; i++) {
		  ss >> var2;
		  array_[i] = var2;
	  }
  }

  size_t size() const {	//Declaring size
    return size_;
  }

  // @location: an index to a location in the chain.
  // @returns the Object at @location.
  // const version.
  // abort() if out-of-range.
  const Object& operator[](size_t location) const { 
	  if (location < 0) {	//if the location, which is the index of the array is less than 0
		  abort();			//abort, simply an error message
	  }
	  else {
		  return array_[location];
	  }
  }

 // @location: an index to a location in the range.
 // @returns the Object at @location.
 // non-const version.
 // abort() if out-of-range.
 Object& operator[](size_t location) { 
	 if (location < 0) {	//if the location, which is the index of the array is less than 0
		 abort();			//abort, simply an error message
	 }
	 else {
		 return array_[location];
	 }
 }

 //  @c1: A chain.
 //  @c2: A second chain.
 //  @return the concatenation of the two chains.
 friend Chain operator+(const Chain &c1, const Chain &c2) {
   Chain temp; 

   temp.size_ = c1.size_ + c2.size_;
   temp.array_ = new Object[temp.size_];					//Dynamic array allocation

   for (unsigned int i = 0; i < c1.size_; i++) {			//Went through 1st array and add it to temp 
	   temp.array_[i] = c1.array_[i];
   }
   int k = c1.size_;
   for(unsigned int j = 0; j < c2.size_; j++) {				//Iterate through 2nd array and add it to temp
	   temp.array_[k] = c2.array_[j];
	   k++;
   }
   return temp;
 }
 
 //Separate + operator overload to cover a different type of string concatination,
 //when they aren't two fixed variables.
 friend Chain operator+(const Chain& p1, const Object& x) {

	 Chain r;
	 r.size_ = p1.size_;
	 r.array_ = new Object[r.size_ + 1];

	 for (unsigned int i = 0; i < p1.size_; i++) {

		 r.array_[i] = p1.array_[i];
	 }

	 r.array_[r.size_ - 1] = x;

	 return r;

 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Chain &a_chain) {

	 out << "[";											//Start off with the beginning braquet
	 for (unsigned int i = 0; i < a_chain.size_; i++) {
		 if (i < a_chain.size_ - 1) {
			 out << a_chain.array_[i] << " ";				//After each <t> in the array, leave a space
		 }
		 else 
		 {			 
			 out << a_chain.array_[i] << "]" << std::endl;	//If finished iterating through the array, then out the end braquet
		 }

	 }

	 if (a_chain.array_ == nullptr) {						// "Base Case" If the array is empty than print the end braquet
		 out << "]" << std::endl;
	 }
	 
	 // Print the chain.
	 return out;
 }
 
 private:
  size_t size_;
  Object *array_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_CHAIN_
