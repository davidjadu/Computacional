wget https://raw.githubusercontent.com/forero/ComputationalMethodsData/master/homework/hw_1/notas_fisicaII_201320.dat
echo Las cantidad de personas que perdieron exactamente un parcial y ganaron la materia fue:
awk < notas_fisicaII_201320.dat '{if(($6>=60)&&(($1<60 && $2>=60 && $3>=60)||($1>=60 && $2<60 && $3>=60)||($1>=60 && $2>=60 && $3<60))) print $1,$2,$3,$6}'|wc -l
echo El mejor promedio en parciales de las personas que pasaron la materia fue:
awk < notas_fisicaII_201320.dat '{if($6>=60) print ($1+$2+$3)/3}'|sort -n | tail -n 1
echo El peor promedio en parciales de las personas que pasaron la materia fue:
awk < notas_fisicaII_201320.dat '{if($6>=60) print ($1+$2+$3)/3}'|sort -n | head -n 1

