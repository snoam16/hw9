#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>
#include "input.h"
int main(int argc ,char** argv)
{ 
//get a rule and pkts and give back the pass pkts
 	check_args(argc,argv);
 	String rule(argv[1]);
 	size_t* size=new size_t;
 	*size=0;
 	String* rule_split;
 	rule.split("=",&rule_split, size);
 	if((int)*size==2)
 	{
 		Field rules(rule_split[0].trim());
 		if(rules.set_value(rule_split[1].trim()))
 		{ 		
  			parse_input(rules);
  		}
  	}
  	if((int)*size != 0)
    {
    	delete[] rule_split;
    }
 	delete size;
 	

 	return 0;
}
