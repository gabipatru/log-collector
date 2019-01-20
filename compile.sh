if [ -f ./log-client.exe ]; then
	rm ./log-client.exe
fi
g++ ./src/main.cpp -o log-client.exe