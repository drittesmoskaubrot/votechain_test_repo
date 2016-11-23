#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <bitset>
#include <vector>

using namespace std;

struct testNode
{
	unsigned int test:1;
};
struct choice_node
{
 
 /**
     [*] prefix in choice row indicates current base level
     
 **/
 
     // #--------> base 10 - 20  
 unsigned int pre_fix1:2;

     // #--------> base 30 - 70
 unsigned int pre_fix2:3;


/*
     // #-------->  base 80 or 90 or 100
*/

 unsigned int pre_fix_for_additional_values1:1;
 unsigned int pre_fix_for_additional_values2:1;
 unsigned int pre_fix_for_additional_values3:1;

/*
     // #-------->  intermediate values from 1 - 7  
*/

 unsigned int c1:1;
 unsigned int c2:2;
 unsigned int c3:3;

/**
    [*] post additional values in choice row replacing missing values 8 9 and 10.

      001 = 8
      010 = 9
      000 = 10
**/

 unsigned int post_fix1:1;
 unsigned int post_fix2:1;
 unsigned int post_fix3:1;


/**
      boolean array keeping track of what values are used in struct
     
      [0] = {true,false} -----> if true reduce loop start index [2] 
      [1] = {true,false} -----> if true reduce loop start index [5]
      [2] = {true,false} -----> if true single 1 bit value c1 
      [3] = {true,false} -----> if true single 2 bit value c2
      [4] = {true,false} -----> if true single 3 bit value c3
      [5] = {true,false} -----> if true pre_fix_ for _additional_values (1,2,3)
      [6] = {true,false} -----> if true post_fix (1,2,3) for pre_fix_for_additional_values (1,2,3)
      [7] = {true,false} -----> if true post fix (1,2,3) for single value

**/


};

bool bit_storage_index[8] ={false};

int main(){

std::string s="";
std::vector<choice_node> choices;     
    choice_node test;
    test.pre_fix1 = 0;
    test.pre_fix2 = 0;
    test.c1=1;
    test.c2=2;
    
    test.post_fix1=1;
    test.post_fix2=1;
    test.post_fix3=1;
    test.pre_fix_for_additional_values1=1;
    test.pre_fix_for_additional_values2=1;
   

 
unsigned int tester = 7;
 test.pre_fix_for_additional_values3=tester;
 test.c3=tester;

   
    printf("%d\n",test.pre_fix1);
    printf("%d\n",test.pre_fix2);
    printf("%d\n",test.c1);
    printf("%d\n",test.c2);
    printf("%d\n",test.c3);
    printf("%d\n",test.pre_fix1);
    printf("%d\n",test.pre_fix2);
    printf("%d\n",test.c1);
    printf("%d\n",test.c2);
    printf("%d\n",test.c3);
    printf("%d\n",test.post_fix1);
    printf("%d\n",test.post_fix2);
    printf("%d\n",test.post_fix3);
    printf("%d\n",test.pre_fix_for_additional_values1);
    printf("%d\n",test.pre_fix_for_additional_values2);
    printf("%d\n",test.pre_fix_for_additional_values3);
    std::cout<<"[*] test node size:"<<sizeof(testNode)<<"\n";
    //Constuct 01: 8 bits initialized to zero
	bitset<8> bitset1;
	cout << "Construction without any parameter. Content of bitset1 :"
	    << bitset1 << endl;
	 
	//Construct 02: Construct it from a integer number
	bitset<3> bitset2(7);
	cout << "[* ]Constructor with int as parameter. size of bitset2: "
	    << sizeof(bitset2) << endl;
	 
	//Construct 03: Construct it from string 
	bitset<8> bitset3(string("11111100"));
	cout << "Constructor with string parameter.Content of bitset3: "
	    << bitset3 << endl;
	//Usage 01: Set and Reset a bit in the bitset
    bitset2.reset(); cout << bitset2 << endl;
    bitset2.set(4); cout << bitset2 << endl;
    bitset2.set(7); cout << bitset2 << endl;
 
    bitset3.set();  cout << bitset3 << endl;
    bitset3.reset(1); cout << bitset3 << endl;
    bitset3.reset(2); cout << bitset3 << endl;
    //Usage 02: Testing a perticular Bit
    cout << "Bitset3: " << bitset3 << endl;
    for (int i=0; i<bitset3.size(); i++)
    {
        if (bitset3.test(i))
            cout << "Bit " << i << " is Set" << endl;
        else
            cout << "Bit " << i << " is Not Set" << endl;
    }
 
    //Usage 03: Number of bits set
    bitset3.reset();
    bitset3.set(2);
    bitset3.set(4);
    bitset3.set(5);
    cout << bitset3.count() << " Bit(s) set" << endl;
    
}