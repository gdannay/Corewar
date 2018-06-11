make -C ~/Corewar/asm
rm ./asm
mv ~/Corewar/asm/asm ./
first=champs
second=vm_champs
files=*.cor

for file in $second/*.s;
do
	echo "----$file---42----"
	./asm_42 $file
	echo "----$file---NO----"
	./asm $file
	echo ""
done

rm ./champs/*.cor
rm ./vm_champs/*.cor
