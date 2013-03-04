/** @file opdracht.h
 * This file contains the doxygen code for this assignment
 */
/*! @mainpage
<p>The assignment:
	Extend the given program with at least one memory administration algorithm.
	You can choose between:
		Best Fit variants, Worst Fit variants,
		Power-Of-Two variants,
		McCusick-Karels
		or some variant of the Buddy Algorithm.
	For further details read your "blokboek".</p>
<p>The given program consist of a 'main' part,
    an instance of the Application class
    and one or more Allocator classes.
<br>The task of 'main' is simple:
<ul>
    <li>It creates an instance of a memory allocator
    <li>It will then pass that memory allocator to the Application
</ul>
<p>The job of the Application is to simulated a client
    that allocates and releases memory.
    It can both be used as a testbed (does your algoritm work correctly)
	or as a performance measuring tool (how well does it perform).
	\note
	Keep in mind that your version of this program must
	also be able to run repeatable scenarios that mimic
	the behaviour of a real world situation.
<p>The job of an Allocator instance is to administrate memory
    according to some algoritm, as implemented in a class derived
    from the Allocator class.</p>
<p>Main understands several commandline options, by default:
<table>
    <tr><td>-s size</td>	<td>size of memory being administrated</td></tr>
    <tr><td>-a count</td>	<td>number of actions (default=10000)</td></tr>
    <tr><td>-t</td>		<td>toggle test mode (default=off)</td></tr>
    <tr><td>-v</td>		<td>toggle verbose mode (default=off)</td></tr>
    <tr><td>-c</td>		<td>toggle check mode (default=off)</td></tr>
    <tr><td>-r</td>		<td>use the random allocator</td></tr>
    <tr><td>-f</td>		<td>use the first fit allocator (lazy)</td></tr>
    <tr><td>-F</td>		<td>use the first fit allocator (eager)</td></tr>
    <tr><td>-n</td>		<td>use the next fit allocator (lazy)</td></tr>
    <tr><td>-N</td>		<td>use the next fit allocator (eager)</td></tr>
</table>
<p>However the exact list is implementation dependent.
	See the 'void tellOptions()'
	and 'void doOptions()' functions in main.cc</p>

\note
	Before compiling the program you have to check common.h and Stopwatch.h
    in order to (de)select platform and compiler dependent choices.

<p>&nbsp;</p>
 */
