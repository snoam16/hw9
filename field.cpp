

#include "field.h"
#include "port.h"
#include "ip.h"
#include <iostream>
#include <cstring>
//constractor
Field::Field(String pattern, field_type type)
{
   	this->pattern =pattern.trim();
    this->type =type;
} 

//constrctot withwout geting th type   
Field::Field(String pattern)
{
    if(pattern.equals("src-ip") || pattern.equals("dst-ip") )
    {
    	this->pattern=pattern.trim();
   		this->type = IP;
   	}
   	else if(pattern.equals("src-port") || pattern.equals("dst-port") )
    {
    	this->pattern=pattern.trim();
   		this->type = PORT;
   	}
   	else
   	{
   		this->type =GENERIC;
   	}
}

//distrectour
Field::~Field()
{
}

//get type
field_type  Field::get_type() const
{
    return type;
}

//set value for the rule limits
bool Field::set_value(String val)
{
    switch(this->get_type())
    {
    case IP:  
      	return ((Ip*)this)->Ip::set_value(val);
    break;
    case PORT: 
     	return ((Port*)this)->Port::set_value(val);
    break;
    default:
     	return false;
    }
    }
    
//check if part of the pkt match the rule
bool Field::match_value(String val) const
    {
    if(val.equals(""))
    {
     	return false;
    }
    String* outputs;
    size_t* size = new size_t;
    *size=0;val.split("=", &outputs, size);
    bool flag=false;
    if(*size==2)
    {
    	if(!(outputs[0].trim().equals((this->pattern))))
    	{
    		if((int)*size != 0)
    		{
    			delete[] outputs;
    		}
    		delete size;
    		return false;
    	}
    
    	switch(this->get_type())
      	{
      	case IP:  
      		flag =((Ip*)this)->Ip::match_value(outputs[1]);
      	break;
     	case PORT: 
     		flag =((Port*)this)->Port::match_value(outputs[1]);
     	break;
     	default:
     		flag= false;
      	}
    }
      	if((int)*size != 0)
    	{
    		delete[] outputs;
    	}
    	delete size;
    	return flag;
    }
    

////check  if the pkt match the rule
bool Field::match(String packet)
{
    String* output;
    size_t* size = new size_t;
    *size=0;
    bool flag=false;
    packet.split(",", &output, size);
    for(int i=0; i < (int)(*size);i++)
    {
    	flag = flag || Field::match_value(output[i].trim());
    }

    if((int)*size != 0)
    {
    	delete[] output;
    }
    
    delete size;
   	return flag;
}
