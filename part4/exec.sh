echo "Experience..."

order=$2
p=$3

cd C/
make clean
make

rm -rf  ../plots/*.png
rm -rf  ../plots/*.plot
		
rm -rf ../plots/exp_$1
mkdir  ../plots/exp_$1

echo "Debut de l'experiece"

./tree_analysis ${order} $p ${ordre_b_arbre}

cd ../plots/
gnuplot -c plot_result --persist

cp -rf *.plot exp_$1/
cp -rf *.png  exp_$1/

cd exp_$1/

for f in * 
do 
	pre="$1"
	mv   "$f" "${pre}_$f"			
done

cd /../..

rm -rf  plots/*.png
rm -rf  plots/*.plot

echo "Fin de l'experience"
