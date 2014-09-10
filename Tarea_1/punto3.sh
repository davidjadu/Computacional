wget https://raw.githubusercontent.com/forero/ComputationalMethodsData/master/homework/hw_1/giro_2014.csv
echo La cantidad de nacionalidades diferentes que participaron en la carrera fue:
awk -F "\"*,\"*" '{if($2!="naz") print $2}' giro_2014.csv | sort | awk '{if($1!=a) {a=$1; print $1}}'| wc -l
echo La cantidad de equipos diferentes que participaron en la carrera fue:
awk -F "\"*,\"*" '{if($2!="naz") print $3}' giro_2014.csv | sort | awk '{if($1!=a) {a=$1; print $1}}'| wc -l
echo Los líderes al final de cada etapa se muestran a continuación, desde la étapa 1 hasta la 24
for i in `seq 4 24`; do echo "awk -F \"\\\"*,\\\"*\" '{if($ 2!=\"naz\" && $ $i !=\"NA\") print $ $i , $ 1}' giro_2014.csv |sort -n | head -n 1 | awk '{print $ 2, $ 3, $ 4}' "; done > nuevo.sh
chmod u+x nuevo.sh
./nuevo.sh
rm nuevo.sh

