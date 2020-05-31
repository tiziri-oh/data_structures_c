echo "Experience : variation de la variable p"

exp="$1"

cd C/
make clean
make
prob=0.0
pas=0.1

rm -rf  plots/*.png
rm -rf  plots/*.plot
		
rm -rf ../plots/exp_$1
mkdir  ../plots/exp_$1

for i in `seq 1 10`;
do 
	echo ""
	prob=$(echo $prob+$pas | bc) 
    
    ./arraylist_analysis $prob

	cd ../plots/
	gnuplot -c plot_result --persist
		
	rm -rf exp_$1_$i
	mkdir  exp_$1_$i

	cp -rf *.plot exp_$1_$i/
	cp -rf *.png  exp_$1_$i/

	cd exp_$1_$i/
	for f in * 
	do 
		pre="${exp}_$i"
		echo "$f -> ../exp_${exp}/${pre}_$f" 
		mv "$f" "../exp_${exp}/${pre}_$f"			
	done
	cd ../
	rm -rf exp_$1_$i/
	echo "Experience exp_${exp}_$i OK"
	cd ../C/
	echo ""
done

echo "Fin de l'experience"
