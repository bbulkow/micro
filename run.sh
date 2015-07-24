echo "pyhon!"
python micro.py
echo "go! no gc"
export GOGC=off
go run micro.go
echo "go! haz gc"
export GOGC=800
go run micro.go
echo "java!"
javac micro.java
java micro
echo "php"
php micro.php
echo "hack"
hh_client
hhvm micro.hh
