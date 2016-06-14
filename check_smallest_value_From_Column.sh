############################################
#	This script will list and sort
#	values of all the columns according
#	to the third column.
###########################################
for f in Iteration_PostionLC1_inclusive_X_-*.txt
do
	echo $f
	#sort -r -nk 3 $f 	# Print each file after sorting the content
	sort -r -nk 5 $f | tail -n1	# Print only smallest value from each file.
	sort -r -nk 5 $f | head -n1	# Print only smallest value from each file.
done
