#ifndef BIT_STRUCT_H
#define BIT_STRUCT_H

class Bit_Struct{

public:
	Bit_Struct();
	~Bit_Struct();

private:
	struct choice_node
    { 
	   unsigned int prefix1:1;
	   unsigned int prefix2:2;
	   unsigned int c1:1;
	   unsigned int c2:2;
	   unsigned int c3:3;
	   bool bit_storage_index[5] ={false};
    };
}

#endif
