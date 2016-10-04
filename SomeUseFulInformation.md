# General Information:



1. 1644:  $799.7\mu A$

	f1->SetParLimits(2,0.2,0.32); 
	
	$Cluster~ Size = 3.32658	\pm0.0149931$

2. 1640: $780.9\mu A$

	f1->SetParLimits(1,2.2,2.39);
	f1->SetParLimits(2,0.2,0.39);

	Cluster Size = $2.39\pm0.0017$
		
3. 1635:  $760.2 \mu A$

	f1->SetParLimits(0,14093,15000);
        f1->SetParLimits(2,0.5,0.52); 
        
       $Cluster~ Size = 1.58819\pm	0.012687$	
       
       Without any setting of paralimits
       $Cluster~size = 1.60847\pm	0.0186002$

4. 1631: $740\mu A$

	f1->SetParLimits(2,0.22,0.25);
	
	$Cluster ~Size = 1.29412\pm	0.00890779$

4. 1627: $720.8\mu A$

	f1->SetParLimits(2,0.12,0.16);
	
	$Cluster~Size = 1.18563\pm	0.00749673$
	
4. 1621: $700.2\mu A$	

	f1->SetParLimits(2,0.09,0.11);
	
	$Cluster~Size = 1.17255\pm 0.00881783$
	
4. 1869: $810.7\mu A$

	f1->SetParLimits(2,0.2,0.35); 
	
	$Cluster ~Size = 3.56871\pm	0.0181471$

5. 1903: $780\mu A$

	f1->SetParLimits(2,0.4,0.50);
	
	$Cluster~Size = 2.06549\pm	0.0157486$
	
6. 1897: $770.2\mu A$

	f1->SetParLimits(2,0.55,0.60);
	
	$Cluster~Size = 1.70319\pm	0.0163755$
	
6. 1892: $760.2\mu A$

	f1->SetParLimits(2,0.55,0.56);
	
	$Cluster~Size = 1.34435\pm	0.015083$	
	
6. 1887: $740.6\mu A$

	f1->SetParLimits(2,0.05,0.19);	
	
	$Cluster~Size = 1.22442\pm	0.00864284$
	
6. 1882: $720.6\mu A$	

	f1->SetParLimits(2,0.04,0.12);
	
	$Cluster~Size = 1.19082\pm	0.0085378$
	
6. 1878: $699.9\mu A$	

	f1->SetParLimits(2,0.04,0.105);
	
	$Cluster~Size = 1.17197\pm	0.01349$
	
7. 2066: $810.1 \mu A$

	f1->SetParLimits(2,0.20,0.28);
	
	$Cluster~Size = 2.39671\pm	0.0115906$


8. 2101: $800\mu A$

	f1->SetParLimits(2,0.20,0.25);
	
	$Cluster~Size = 2.0863\pm	0.0102389$
	
9. 2096: $780.5 \mu A$

	f1->SetParLimits(2,0.32,0.35);
	
	$Cluster~Size = 1.6427\pm	0.00919847$
	
* 2091: $760.1\mu A$

	f1->SetParLimits(2,0.31,0.325);	
	
	$Cluster~Size = 1.2979\pm	0.00921625$
	
* 2121: $750.0\mu A$	

	f1->SetParLimits(2,0.22,0.235); 
	
	$Cluster~Size = 1.26376\pm	0.0088665$
	
* 2086:  $740.1\mu A$	

	f1->SetParLimits(2,0.15,0.175); 
	
	$Cluster~Size = 1.20789\pm	0.0077768$
	
* 2117: $730.0\mu A$

	f1->SetParLimits(2,0.05,0.145);	
	
	$Cluster~Size = 1.20733\pm	0.00758641$
	
* 2112: $710.1\mu A$	

	f1->SetParLimits(2,0.05,0.115); 
	
	$Cluster~Size = 1.16312\pm	0.0104699$
	
* 2077: $700.0\mu A$	

	$Cluster~Size = 1.16154\pm	0.0131358$
	


-------------
1. Change range from (0,100) $\rightarrow$ (0,102).
2. Run Range to analyze:
	1. 1592-1646 : 2014H4A	: 
		* Latency 17	: No prob : (5,2)
		* 1593, 1617, 1621, 1627, 1631, 1635, 1640, 1644
	2. 1869-1903 : 2014H4C	: 
		* Latency 17	: HV Swap : (8,2)
		* 1878, 1882, 
	3. 2065-2123 : 2014H4C	: 
		* Latency 17	: HV Swap : (1,2)
3. Pitch of three sectors:

		 (1,2) = 1.0598 mm
		 (5,2) = 0.816915 mm
		 (8,2) = 0.674115 mm

## Fitting Setting for Cluster Size Distribution

| Run Number 	| ParNumber 	| ParMin  	| ParMax	|
|-----------	|---------------	|		|		|
|1644	|2	| 0.2	|0.32	|
|1640	|1	|2.2	|2.39	|
|	|	2	|0.2|0.39



#Run Specific Setting For All Codes

## RunRange 1869-1903

1. Run number 1887
	* Strip Info:
		* g1x :  Mean = 109.4, Std. Dev = 56.24
		* g1y :  Mean = 128.4, Std. Dev = 47.49
		* g2x :  Mean = 104.1, Std. Dev = 55.25
		* g2y :  Mean = 130.6, Std. Dev = 46.83
		* g3x :  Mean = 109.7, Std. Dev = 54.75
		* g3y :  Mean = 131.4, Std. Dev = 46.01
	* Cluster Info:
		* g1x :  Mean = 2.109, Std. Dev = 1.491
		* g1y :  Mean = 2.057, Std. Dev = 1.474
		* g2x :  Mean = 3.323, Std. Dev = 2.147
		* g2y :  Mean = 2.970, Std. Dev = 2.013
		* g3x :  Mean = 2.546, Std. Dev = 1.654
		* g3y :  Mean = 2.427, Std. Dev = 1.623
		
## RunRange 1592-1646

1. Run numbers on platue
	1. 740uA: Run1631
	2. 760uA: Run1635
	3. 780uA: Run1640, Run1593
	4. 800uA: Run1644

2. AlignTrackers_Shift.C: Histogram ranges
	1. g2x: (-6, 1, 100)
	2. g2y: (-1.5, 2.8, 61)
	3. g3x: (-1, 2.5, 50)
	4. g3y: (-1.5, 1, 36)

3. AlignTrackers_shift_rotate.C: Histogram ranges
	1. g2x: (-6, 1, 100)
	2. g2y: (-1.5, 2.8, 61)
	3. g3x: (-1, 2.5, 50)
	4. g3y: (-1.5, 1, 36)

4. AlignTrackers_optimizeRotation.C

5. AlignGEM_XYoffsets.C

6. AlignGEM_rotate.C
