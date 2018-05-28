first=champs
second=vm_champs
files=*.cor

for file in $second/*.s;
do
	echo "----$file-42--"
	./asm_42 $file
	echo ""
	echo "----$file-NO--"
	comp/./asm $file
	echo ""
	echo ""
done

for file in $second/*cor;
do
	echo "-----$file-----"
	diff $file comp/$file
	echo ""
	echo ""
done
