#include "string.h"
#include <iostream>
#include <cstring>
#define IPSIZE 4


//constructor of empty string
    
String::String()
{
    	data = NULL;
    	length=0;
}


// constructor of string from other string
    
String::String(const String &str)
{
    if(str.data != NULL)
    {
        this-> length = str.length+1;
    
       	this->data = new char[(int)(this->length)];
       	
       	strncpy(this->data, str.data,(int)(length));
    }
    else
    {
     	data = NULL;
    	length=0;
    }
}


 //constructor of string from char array
    
String::String(const char *str)
{
    if(str != NULL)
    {
    	this-> length = strlen(str) +1;
    	this-> data = new char[(int)(this->length) ];
    	strncpy(this->data, str, length );       
    }
    else
    {
     	data = NULL;
    	length=0;
    }
}
    	
    //distructor

String::~String()
{
    if(this->data != NULL)
    {
    	delete[] this->data;
    }
}

//assigment opertor from string
String& String::operator=(const String &rhs)
{
    if(this==&rhs)
    {
    	return *this;
    }
 	if(this->data != NULL)
    {
    	delete[] this->data;
    }
    if(rhs.data != NULL)
    {    
        this-> length = rhs.length+1;
    
       	this->data = new char[(int)(this->length) ];
       	
       	strncpy(this->data, rhs.data,(int)(length) );
    }
    else
    {
     	data = NULL;
    	length=0;
    }
    
    return *this;
}

    	

 //assigment opertor from char array
    
String& String::operator=(const char *str)
{

 	if(this->data != NULL)
   	{
    	delete[] this->data;
    }
    if(str != NULL)
    {
    	this-> length = strlen(str)+1;
    	this-> data = new char[(int)(this->length) ];
    	strncpy(this->data, str, length);       
    }
    else
    {
     	data = NULL;
    	length=0;
    }
    return *this;
}

//return true if this data equals rhs data
bool String::equals(const String &rhs) const
{
    if((rhs.data ==NULL) && (data ==NULL))
    {
    	return true;
    }
    if((rhs.data != NULL) && (strncmp(this->data, rhs.data,(int)(length)) == 0))
    {
    	    return true;
    }
    return false;
}

//return true if this data equals rhs 
bool String::equals(const char *rhs) const
{
    if((rhs ==NULL) && (data ==NULL))
    {
    	return true;
    }

    if((rhs!=NULL) &&(std::strncmp(data, rhs,length) == 0))
    {
    	    return true;
    }
    return false;
}

/**
    * splits this to several sub-strings according to delimiters.
    * Allocates memory for output that the user must delete (using delete[]).
    * @note Does not affect this.
    * @note If "output" is set to NULL, do not allocated memory, only
    * compute "size".
    */
void String::split(const char *delimiters, String **output, size_t *size) const
{
   
    if(size == NULL || delimiters==NULL || data==NULL)
    {
    	return;
    }
   
    int delimitersSize =strlen(delimiters),lastDelim=0;
    *size =1;
   //comput size
    for(int i=0; i<(int)(this->length); i++)
    {
    	for(int j=0; j<delimitersSize;j++)
    	{
    		if(this-> data[i]== delimiters[j])
    		{
    			if(i>lastDelim)
    			{                    
    				(*size)+=1;
    			}
    			lastDelim=i+1;
     		}
    	}
    }
    if(output == NULL)
    {
     	return;
    }
    
    lastDelim=0;
    *output=new String[(int)(*size)];
    *size =0;
    //set output
    for(int i=0; i<(int)(this->length); i++)
    {
    	for(int j=0; j<delimitersSize;j++)
    	{
    		if(this-> data[i]== delimiters[j])
    		{
    			if(i>lastDelim)
    			{
              		(*output)[(int)(*size)] =
              			String(strtok((data+lastDelim) ,(delimiters +j)));
               		(*size)+=1;
               	}
            	lastDelim = i+1;
     		}
      	}
    }
   	(*output)[(int)(*size)] = String(strtok((data+lastDelim), "\n"));
 	(*size)+=1;
}

    		
    			
    			
    	


//  return this converted to an integer. Returns 0 on error.
    
int String::to_integer() const
{
    int ipPart=0, returnVal=0;
    size_t* size =new size_t;
    size_t* idx =new size_t;
    String* output;
    this->split(".", &output, size);
    if((int)*size == IPSIZE)
    {
    	for(int i=0; i<IPSIZE; i++)
    	{
    		
    		ipPart=output[i].trim().to_integer();
    		if(ipPart<256 && ipPart>0)
    		{
    			returnVal+= ipPart<<(24-8*i );
    		}
    	}
    	delete idx;
    	if((int)*size != 0)
    	{
    		delete[] output;
    	}
       	delete size;
        return returnVal;
    }
    else if(*size == 1)
    {
    	*idx=0;
    	
    	returnVal = std::stoi(data, idx, 10);
    	delete idx;
    	if((int)*size != 0)
    	{
    		delete[] output;
    	}
        delete size;
    	return returnVal;
    }
    else
    {
    	delete idx;
    	if((int)*size != 0)
    	{
    		delete[] output;
    	}
        delete size;
       	return 0;
    }
}
  //trim white-spaces. Does not change this.
    
String String::trim() const
{
    int head=0,tail=(int)(this->length)-3;
    if (this->data != NULL)
    {
    
    	while((isspace(data[head])) && (head<=tail))
    	{ 
     		head++;
       	}

    	while((isspace(data[tail])) && (tail>=head))
    	{ 
      		tail--;
    	}
    	
    		
      	tail++;
      	if(tail<=head)
      	{
       		return String();
      	}
      	if(tail==((int)(this->length)-2))
      	{
      		
      			
      		if(head==0)
      		{
      			return *this;
      		}
      		
      		String strTrimed1 =((this->data)+head);
      		return strTrimed1;
      	}
      	if(tail > head)
      	{
      		
        	char* strtemp1=new char[tail-head+1];
   	    	strncpy(strtemp1, (&(this->data)[head]) ,(tail-head));
   	    	strtemp1[tail-head]='\0';
       		String strTrimed (strtemp1);
       		delete[] strtemp1;
         	return strTrimed;
      	}
    
    }
    return String();
}

    
    
    	
    	
    

