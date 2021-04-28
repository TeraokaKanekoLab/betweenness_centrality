bc() {
    echo "g++ src/main.cpp -o ./main --std=c++17"
    g++ src/main.cpp -o ./main --std=c++17
    echo "./main $1 $2 $3"
    ./main $1 $2 $3
    rm ./main
}

case $1 in
"all")
    bc $2 $3 $4
    ;;
esac
