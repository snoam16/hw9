#!/bin/bash
#########################################################################
# get rules and pkts and print the pkts that fit for at lest one rule
#########################################################################

#clean the rules input forom coments empty line and spaces
sed  's/\#.*//' $1 >rulestemp.txt
sed '/^[[:space:]]*$/d' rulestemp.txt >rulestemp2.txt
cat rulestemp2.txt| tr -d  ' '  > rulesclean.txt 
touch outtemp.txt
cat $2 > pkt.txt

#check the rule for all the pkts
while read rule; do
	((counter=0))
	rules=`echo "$rule"|tr "," "\n"`
	touch oneruleout.txt 
	for partrule in $rules; do
		[ -z "$partrule" ] && continue
		./firewall.exe "$partrule" <pkt.txt >>oneruleout.txt
		((counter=counter+1))
	done
	sort oneruleout.txt|uniq -c >oneruleout2.txt
	rm oneruleout.txt 
	while read line; do 
		repets=`echo ${line:0:1}`
		if((repets == counter)); then
			echo "$line" |cut -c2- >>outtemp.txt
		fi
	done<oneruleout2.txt
				
done<rulesclean.txt

#sort and clean the output from spaces, empty lines and doubble lines
sort outtemp.txt|uniq | tr -d  ' '| sed '/^[[:space:]]*$/d' | tr -d  ' '>out.txt
cat out.txt
rm outtemp.txt oneruleout2.txt rulesclean.txt 
rm rulestemp2.txt rulestemp.txt pkt.txt
 
