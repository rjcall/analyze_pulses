This program analyzes digitized data for pulses. The data comes from an actual digitizer that reports
voltages (except all the data has been reversed by the hardware).

The data is quite jagged, so for finding pulses the data will be smoothed. 

Smooth data: 

the first 3 numbers from the original negated data are copied. Then, starting with the 4th point of the file (position [3], of course), and
ending with the 4th from the last, replace each of those points with the following weighted average of its neighbors

Then the last 3 numbers are copied over to fill out the smoothed vector.


 A pulse is detected by looking for a rise over three consecutive points. If the rise (yi+2 – yi) exceeds vt, (for “voltage threshold” – supplied by an input parameter), then a pulse begins at position i. After finding a pulse, the data is moved through the data starting at yi+2 until the samples start to decrease before looking for the next pulse.
The program process all files with a “.dat” extension in the current directory.
 There can be an arbitrary number of such files, and an arbitrary number of sample data values within each file. 

Where pulses are found, and also the “area” underneath the pulses is printed. (The area is merely the sum of the values starting at the pulse start
and going for width samples (another input parameter), or until the start of the next pulse, whichever comes first.)

To distinguish “piggyback” pulses (where a pulse is adjacent to another) from a wide pulse with some variation to it. To distinguish these, we use the following parameters:

Parameter Description
drop_ratio A number less than 1
below_drop_ratio The number of values less than drop_ratio
pulse_delta The gap between pulses to look for piggybacks the program checks to see if the start of a pulse is followed by another pulse that starts
within (<=) pulse_delta positions of it. If this occurs, how many points between the peak of the first pulse(inclusive) and the start of the second pulse (non-inclusive) are strictly less than
drop_ratio times the height of the peak of the first pulse. If the number exceeds below_drop_ratio, the
first pulse is omitted from further consideration (it is not a pulse of interest).

All parameters are necessary and none others are allowed. Blank lines are allowed and should also be ignored.
