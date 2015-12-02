###############################################################################
# plot_timing_ats_http.gp
# 
# Plotting timing output from Apache Bench with gnuplot
###############################################################################

# Output to a jpeg file
set terminal jpeg size 1200,800
# Set the aspect ratio of the graph
set size 1, 1
# The file to write to
set output out_file
# Graph title
set title plot_title
# Place the legend/key
set key left top
# Draw gridlines oriented on the y axis
set grid y
# Label the x-axis
set xlabel 'filesize (bytes)'
# Label the y-axis
set ylabel "response time (ms)"
# Use tabs as the delimiter
set datafile separator '\t'
# Plot the data
plot data_file using 1:2 title 'response time' with lines
exit
