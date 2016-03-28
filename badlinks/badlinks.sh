for i in $(find -L $1 -type l -mtime +7)
do
	[ ! -e "$i" ] && echo $i
done 
