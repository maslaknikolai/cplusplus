clang++ main.cpp -o app && ./app && rm app

rm -rf build && \
mkdir build && \
cd build && \
cmake .. && \
cmake --build . && \
./app

https://youtu.be/-TkoO8Z07hI?si=pLvjIFNngcGL52d6&t=9190
