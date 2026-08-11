> limits_args.txt
while IFS= read -r line; do
    echo $line SB2 SR2 VB1 VS2 All1p1_Only2p1 >> limits_args.txt
    echo $line SB2 SR2 VB1 VS2 All2p1_Only1p1 >> limits_args.txt
done < ../raw_nano/GoodMassPoints.txt
