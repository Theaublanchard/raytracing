make

echo
echo Launching program
echo
./myprogram

echo
echo Done.
echo

make clean

pnmtopng out.ppm > out.png

rm ./myprogram
rm ./out.ppm