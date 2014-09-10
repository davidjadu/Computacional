wget https://raw.githubusercontent.com/forero/ComputationalMethodsData/master/hands_on/solar/monthrg.dat
echo El promedio de manchas solares en 11/1993 fue de:
awk < monthrg.dat '{if($1==1993 && $2==11) print $4}'
echo La cantidad de meses desde 1900 hasta 1950 que tuvieron m�s de 30 manchas solares fueron:
awk < monthrg.dat '{if($1<1951 && $1>1899 && $4>30) print $4}' | wc -l
echo El a�o y el mes con m�s manchas solares en toda la histroia fue:
sort -k 4n monthrg.dat | tail -n 1 | awk '{print $1,$2}'