#!/usr/local/bin/gnuplot -persist
#
#    
#    	G N U P L O T
#    	Version 4.4 patchlevel 3
#    	last modified March 2011
#    	System: Darwin 10.8.0
#    
#    	Copyright (C) 1986-1993, 1998, 2004, 2007-2010
#    	Thomas Williams, Colin Kelley and many others
#    
#    	gnuplot home:     http://www.gnuplot.info
#    	faq, bugs, etc:   type "help seeking-assistance"
#    	immediate help:   type "help"
#    	plot window:      hit 'h'
# set terminal x11 
# set output
unset clip points
set clip one
unset clip two
set bar 1.000000 front
set border 31 front linetype -1 linewidth 1.000
set xdata
set ydata
set zdata
set x2data
set y2data
set timefmt x "%d/%m/%y,%H:%M"
set timefmt y "%d/%m/%y,%H:%M"
set timefmt z "%d/%m/%y,%H:%M"
set timefmt x2 "%d/%m/%y,%H:%M"
set timefmt y2 "%d/%m/%y,%H:%M"
set timefmt cb "%d/%m/%y,%H:%M"
set boxwidth
set style fill  empty border
set style rectangle back fc lt -3 fillstyle   solid 1.00 border lt -1
set style circle radius graph 0.02, first 0, 0 
set dummy x,y
set format x "% g"
set format y "% g"
set format x2 "% g"
set format y2 "% g"
set format z "% g"
set format cb "% g"
set angles radians
unset grid
set key title ""
set key inside right top vertical Right noreverse enhanced autotitles nobox
set key noinvert samplen 4 spacing 1 width 0 height 0 
set key maxcolumns 0 maxrows 0
unset label
unset arrow
set style increment default
unset style line
unset style arrow
set style histogram clustered gap 2 title  offset character 0, 0, 0
unset logscale
set logscale x 10
set offsets 0, 0, 0, 0
set pointsize 1
set pointintervalbox 1
set encoding default
unset polar
unset parametric
unset decimalsign
set view 60, 30, 1, 1
set samples 100, 100
set isosamples 10, 10
set surface
unset contour
set clabel '%8.3g'
set mapping cartesian
set datafile separator whitespace
unset hidden3d
set cntrparam order 4
set cntrparam linear
set cntrparam levels auto 5
set cntrparam points 5
set size ratio 0 1,1
set origin 0,0
set style data points
set style function lines
set xzeroaxis linetype -2 linewidth 1.000
set yzeroaxis linetype -2 linewidth 1.000
set zzeroaxis linetype -2 linewidth 1.000
set x2zeroaxis linetype -2 linewidth 1.000
set y2zeroaxis linetype -2 linewidth 1.000
set ticslevel 0.5
set mxtics default
set mytics default
set mztics default
set mx2tics default
set my2tics default
set mcbtics default
set xtics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set xtics autofreq  norangelimit
set ytics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set ytics autofreq  norangelimit
set ztics border in scale 1,0.5 nomirror norotate  offset character 0, 0, 0
set ztics autofreq  norangelimit
set nox2tics
set noy2tics
set cbtics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set cbtics autofreq  norangelimit
set title "" 
set title  offset character 0, 0, 0 font "" norotate
set timestamp bottom 
set timestamp "" 
set timestamp  offset character 0, 0, 0 font "" norotate
set rrange [ * : * ] noreverse nowriteback  # (currently [8.98847e+307:-8.98847e+307] )
set trange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set urange [ * : * ] noreverse nowriteback  # (currently [-10.0000:10.0000] )
set vrange [ * : * ] noreverse nowriteback  # (currently [-10.0000:10.0000] )
set xlabel "" 
set xlabel  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set x2label "" 
set x2label  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set xrange [ * : * ] noreverse nowriteback  # (currently [-2.00000:2.00000] )
set x2range [ * : * ] noreverse nowriteback  # (currently [-1.30103:1.96690] )
set ylabel "" 
set ylabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by -270
set y2label "" 
set y2label  offset character 0, 0, 0 font "" textcolor lt -1 rotate by -270
set yrange [ * : * ] noreverse nowriteback  # (currently [-5.00000:35.0000] )
set y2range [ * : * ] noreverse nowriteback  # (currently [-0.704335:34.3592] )
set zlabel "" 
set zlabel  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set zrange [ * : * ] noreverse nowriteback  # (currently [-10.0000:10.0000] )
set cblabel "" 
set cblabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by -270
set cbrange [ * : * ] noreverse nowriteback  # (currently [8.98847e+307:-8.98847e+307] )
set zero 1e-08
set lmargin  -1
set bmargin  -1
set rmargin  -1
set tmargin  -1
set locale "en_US.UTF-8"
set pm3d explicit at s
set pm3d scansautomatic
set pm3d interpolate 1,1 flush begin noftriangles nohidden3d corners2color mean
set palette positive nops_allcF maxcolors 0 gamma 1.5 color model RGB 
set palette rgbformulae 7, 5, 15
set colorbox default
set colorbox vertical origin screen 0.9, 0.2, 0 size screen 0.05, 0.6, 0 front bdefault
set loadpath 
set fontpath 
set fit noerrorvariables
GNUTERM = "x11"
set terminal postscript eps enhanced color
set output 'timescale.eps'
data1 = '../data/standard-frag-post.txt'
data2 = '../data/standard-coag-post.txt'
reset
bm = 0.15
lm = 0.15
rm = 0.85
gap = 0.03
size = 0.7
y1 = -0.8; y2 = 0; y3 = 0.01; y4 = 40
y21 = -0.8; y22 =0; y23 = 0.01; y24 = 10 
ratio = 0.5
set multiplot
set xlabel 'Mass/M_{sun}' font "Times new roman, 20"
set border 1+2+8
set xtics nomirror font ",20"
set ytics 0.2 nomirror font ",20"
set y2tics 0.2 nomirror font ",20"
set lmargin at screen lm
set rmargin at screen rm
set bmargin at screen bm
set tmargin at screen bm + size * ratio

#set style rectangle back
#set object 1 rect from graph 0.6, graph 0.08 to graph 0.95, graph 0.7 fs transparent
set yrange [y1:y2]
set y2range [y21:y22]
set xrange [0.05:40]
set y2tics nomirror
set log x
width = 2
set key at graph 0.85, graph 0.5  

plot data1 u 1:3 w l lw width lc rgb '#FF8888' lt 5 axis x1y1 title '1Myr',\
data1 u 1:5 w l lw width lc rgb '#FF6666' lt 4 axis x1y1 title '2Myr',\
data1 u 1:7 w l lw width lc rgb '#FF4444' lt 3 axis x1y1 title '3Myr',\
data1 u 1:9 w l lw width lc rgb '#FF2222' lt 2 axis x1y1 title '4Myr',\
data1 u 1:11 w l lw width  lc rgb '#FF0000' lt 1 axis x1y1 title '5Myr',\
data2 u 1:3 w l lw width lc rgb '#8888FF' lt 5 axis x1y2 notitle,\
data2 u 1:5 w l lw width lc rgb '#6666FF' lt 4 axis x1y2 notitle,\
data2 u 1:7 w l lw width lc rgb '#4444FF' lt 3 axis x1y2 notitle,\
data2 u 1:9 w l lw width lc rgb '#2222FF' lt 2 axis x1y2  notitle,\
data2 u 1:11 w l lw width lc rgb '#0000FF' lt 1 axis x1y2 notitle

unset xtics
unset xlabel
unset ytics
unset ylabel
unset border 
set xrange [GPVAL_X_MIN:GPVAL_X_MAX]
#
set label "abla" at graph 0.75, graph 0.6
set label "coag" at graph 0.85, graph 0.6
set key box at graph 0.95, graph 0.66 tc rgb 'black' 
plot NaN t " " w l lc rgb '#FFFFFF',NaN t " " w l lc rgb '#FFFFFF',NaN t "          " w l lc rgb '#8888FF' lt 5, \
NaN t " " w l lw width lc rgb '#6666FF' lt 4, \
NaN t " " w l lw width lc rgb '#4444FF' lt 3, \
NaN t " " w l lw width lc rgb '#2222FF' lt 2, \
NaN t " " w l lw width lc rgb '#0000FF' lt 1

#unset object 1
set border 2+4+8
set bmargin at screen bm + size * ratio + gap
set tmargin at screen bm + size + gap
unset xtics
unset ytics
unset y2tics
unset xlabel
unset label
set yrange [y3:y4]
set y2range [y23:y24]
set log x
set xrange [0.05:40]
set ytics 0.1 nomirror font ",20"
set y2tics 0.1 nomirror font ",20"

set label 'Ablation rate (Myr^{-1})' at screen 0.05, bm + 0.5 * (size + gap) offset 0,-strlen("Ablation rate (Myr^{-1})")/4.0 rotate by 90 font "Times new roman ,20"

set label 'Coagulation rate (Myr^{-1})' at screen 0.95, bm + 0.5 * (size + gap) offset 0,-strlen("Coagulation rate (Mry^{-1})")/4.0 rotate by 90 font "Times new roman ,20"


set arrow from screen lm - gap / 4.0, bm + size * ratio - gap / 4.0 to screen \
lm + gap / 4.0, bm + size * ratio + gap / 4.0 nohead

set arrow from screen lm - gap / 4.0, bm + size * ratio - gap / 4.0  + gap to screen \
lm + gap / 4.0, bm + size * ratio + gap / 4.0 + gap nohead

set arrow from screen rm - gap / 4.0, bm + size * ratio - gap / 4.0 to screen \
rm + gap / 4.0, bm + size * ratio + gap / 4.0 nohead

set arrow from screen rm - gap / 4.0, bm + size * ratio - gap / 4.0  + gap to screen \
rm + gap / 4.0, bm + size * ratio + gap / 4.0 + gap nohead

set log x
set log y
set log y2
unset key
#set y2tics nomirror
#set label "1Myr" at graph 0.6, graph 0.85 tc rgb '#888888'
#set label "2Myr" at graph 0.71, graph 0.85 tc rgb '#666666'
#set label "3Myr" at graph 0.77, graph 0.85 tc rgb '#444444'
#set label "4Myr" at graph 0.83, graph 0.85 tc rgb '#222222'
#set label "5Myr" at graph 0.9, graph 0.85 tc rgb '#000000'
plot data1 u 1:3 w l lw width lc rgb '#FF8888' lt 5 axis x1y1 ,\
data1 u 1:5 w l lw width lc rgb '#FF6666' lt 4  axis x1y1,\
data1 u 1:7 w l lw width lc rgb '#FF4444' lt 3  axis x1y1,\
data1 u 1:9 w l lw width lc rgb '#FF2222' lt 2  axis x1y1,\
data1 u 1:11 w l lw width lc rgb '#FF0000' lt 1 axis x1y1,\
data2 u 1:3 w l lw width lc rgb '#8888FF' lt 5  axis x1y2,\
data2 u 1:5 w l lw width lc rgb '#6666FF' lt 4  axis x1y2,\
data2 u 1:7 w l lw width lc rgb '#4444FF' lt 3  axis x1y2,\
data2 u 1:9 w l lw width lc rgb '#2222FF' lt 2  axis x1y2,\
data2 u 1:11 w l lw width lc rgb '#0000FF' lt 1 axis x1y2

unset multiplot

set output
set terminal x11

#    EOF
