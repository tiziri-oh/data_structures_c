echo "Nom de l'experience : $1 nbfois: $2"

rm -rf  plots/*.png
rm -rf  plots/*.plot

rm -rf plots/exp_$1
mkdir  plots/exp_$1

for i in `seq 1 $2`;
do 
	echo ""
	cd C/
	make
	./arraylist_analysis
	make clean
	cd ..

	cd CPP/
	make
	./arraylist_analysis
	make clean
	cd ..

	cd Java
	javac *
	java Main
	cd ..

	cd Python
	python main.py
	cd ..

	cd plots/
	gnuplot -c plot_result --persist

	rm -rf exp_$1_$i
	mkdir  exp_$1_$i

	cp -rf *.plot exp_$1_$i/
	cp -rf *.png  exp_$1_$i/

	cd exp_$1_$i
	
	for f in *
	do 
		pre="$1_$i"
		mv "$f" "../exp_$1/${pre}_$f"			

	done

	cd ../
	rm -rf exp_$1_$i/
	echo "Experience exp_$1_$i OK"
	cd ../

	echo ""
done