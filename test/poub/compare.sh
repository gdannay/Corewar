make -C ~/Corewar/asm
rm ./asm
mv ~/Corewar/asm/asm ./
first=vm_champs
second=vm_champs
files=*.cor

for file in $second/*.s;
do
	echo "----$file-42--"
	./asm_42 $file
	echo ""
	echo "----$file-NO--"
	./asm $file
	echo ""
	echo ""
done

for file in $second/*cor;
do
	echo "-----$file-----"
	diff $file $file
	echo ""
	echo ""
done
