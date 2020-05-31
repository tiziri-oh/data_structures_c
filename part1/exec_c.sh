echo "Nom de l'experience : $1"

rm -rf  plots/*.png
rm -rf  plots/*.plot

cd C/
make
./arraylist_analysis
make clean
cd ..

cd plots/

gnuplot -c plot_result_c --persist

rm -rf exp_$1

mkdir exp_$1

cp -rf *.plot exp_$1/
cp -rf *.png  exp_$1/

cd exp_$1

for f in *
do
	mv -- "$f" "$1_$f"
done

cd ../../
