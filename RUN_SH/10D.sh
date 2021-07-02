


j=1
i=1
for (( i; i<9; i=i+1 ))
do   
     for (( j; j<11; j=j+1 ))
     do
          echo $i $j
          ./LSHADE 10 $j $i  >> LSHADE_CEC21_10D.txt

     done
     j=1
done


