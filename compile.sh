if [ -f ./log-client.exe ]; then
	rm ./log-client.exe
fi
g++ ./src/main.cpp -lcurl -o log-client.exe