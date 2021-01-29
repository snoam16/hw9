#include "ip.h"
#include <iostream>
#include <cstring>
#include <cmath>

//consractour
Ip::Ip(String pattern):Field::Field(pattern,IP)
{
}

//set value for ip rule limits
bool  Ip::set_value(String val)
{
    unsigned int ipValue=0,bitValue=0,lowb=0,highb=0;
    String* output;
    size_t* size = new size_t;
    *size=0;
    val.split("/", &output, size);
    if(*size == 2)
    {
    	
    	ipValue=(output[0]).trim().to_integer();
    	bitValue=(output[1]).trim().to_integer();
    	for(int i=0;i<32;i++)
    	{
    		if((32-i)<= (int)bitValue)
    		{
    			lowb+=pow(2,i);
    		}
    		else
    		{
    			highb+=pow(2,i);
    		}
    	}
    	low = ipValue & lowb;
    	high = ipValue | highb;
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

//check if ip part of the pkt match the rule
bool  Ip::match_value(String val) const
{
    if(val.equals(""))
    {
     	return false;
    }
     	    
    unsigned int value=0;
    value =(unsigned int)(val).trim().to_integer();
    if(value>=low && value<= high)
    {
  		return true;
   	}
    	    
	return false;
}
    		
    
    

