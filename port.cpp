#include "port.h"
#include <iostream>
#include <cstring>

//constructor
Port::Port(String pattern):	Field::Field(pattern,PORT)
{
}

//set value for port rule limits
bool Port::set_value(String val)
{
    String* output;
    size_t* size = new size_t;
    *size=0;
    val.split("-", &output, size);
    if(*size == 2)
    {
    	range[0]=(output[0]).trim().to_integer();
    	range[1]=(output[1]).trim().to_integer();
    	if((int)*size != 0)
    	{
    		delete[] output;
    	}
    	delete size;
    	return true;
    }
    if((int)*size != 0)
    {
    	delete[] output;
    }
    delete size;
	return false;
}

//check if port part of the pkt match the rule
bool Port::match_value(String val) const
{
    if(val.equals(""))
    {
     	return false;
    }
     	    
    int value=0;

    value =(val).trim().to_integer();
    if(value>=range[0] && value<= range[1])
    {
    	return true;
    }
    
    
    return false;
}
    		
    


