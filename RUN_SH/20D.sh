


j=1
i=1
for (( i; i<9; i=i+1 ))
do   
     for (( j; j<11; j=j+1 ))
     do
          echo $i $j
          ./LSHADE 20 $j $i  >> LSHADE_CEC21_20D.txt

     done
     j=1
done


