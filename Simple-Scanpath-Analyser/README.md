# Simple-Scanpath-Analyser

## Overview
**Autism Spectrum Disorder (ASD)** is a neurodevelopmental disorder characterised by differences in communication and social interaction [1, 2]. Recent research studies have analysed the eye movements of people with and without autism recorded while interacting with web pages, and have found that people with autism tend to have different processing strategies in comparison with people without autism when they interact with web pages [1, 2].

**Eye tracking** is the process of recording the eye movements of people to understand where they look at, called fixations, and how long these fixations last. The series of their fixations represent their scanpaths. Scanpaths are usually analysed based on the **areas of interest (AOIs)** of visual stimuli, especially which AOIs are frequently used and in which order. Figure 1 shows an example of a scanpath of a particular person on one web page of Wordpress.com where the red rectangles show the AOIs of the web page, and the yellow circles show the person’s fixations - the radius of each circle is directly proportional to the duration of its corresponding fixation.
<p align="center">Figure 1. A scanpath of a particular user on one web page of Wordpress.com</p>
<p align="center"><img src="https://i.ibb.co/cY3D6Vs/image-2022-09-10-200017262.png" width="800px"></p>

To analyse scanpaths based on AOIs, they are first represented as string sequences. For example, if a person looks at the AOIs L, M, P, and R respectively, his/her scanpath is represented as LMPR. In this assignment, you will need to develop another simple scanpath analyser to check whether a given pattern is available in a set of scanpaths of people with and without autism.

This application will start by taking the name of the two files from the user where the first file includes a number of scanpaths for people with autism and another one includes a number of scanpaths for people without autism, which are represented as string sequences based on ten AOIs named with digits from zero to 9. These files may include a different number of scanpaths, and each line in these files represent a different scanpath. You can assume that the maximum length of a scanpath is 100. An example content of a file is given below:

    6547382712384758123
    3547712364687
    847364537292
    9374638473682
    8162537252

This application will then ask the user to enter the pattern to be detected (such as, 123). It will then show the scanpaths that include the pattern for people with and without autism by highlighting the patterns with square brackets. It will also show how many pattern matches are found in how many scanpaths and also the most frequent AOI before the pattern for each group of people. If there are multiple of them, all of them should be printed. A sample run is provided below:

    Enter the file name for people with autism: peoplewithautism.txt
    Enter the file name for people without autism: peoplewithoutautism.txt
    Enter the pattern: 123
    Detected patterns for people with autism:
    1. 65473827[123]84758[123]
    2. 35477[123]64687
    3 patterns detected in 2 scanpaths
    The most frequent AOI before the pattern is/are 7
    Detected patterns for people without autism:
    None

## Implementation Requirements
This application will have one linked-list for people with autism and another one for people without autism. In each node of the linked lists, the string representation of a scanpath should be kept. You will need to implement the following functions and call them appropriately in the main function. You can also implement some helper functions.
* **createScanpathList:** This function takes the name of the file containing a number of scanpaths which are represented as string sequences and creates a linked-list where each node contains a string representation of a single scanpath. It will return the created list.
* **searchPattern:** This function takes the pattern and the linked lists of people with and without autism to check whether the pattern is available in the scanpaths of people with and without autism by using the Rabin-Karp Algorithm where d=10 (since there are 10 digits) and q=11. If the pattern is detected in a scanpath, it will be highlighted with square brackets as shown above. The general pseudo-code of the Rabin-Karp Algorithm is given below.
<p align="center"><img src="https://i.ibb.co/7gfGrXw/image-2022-09-10-200617797.png"></p

As mentioned above, this function will also show how many pattern matches are found in how many scanpaths and also the most frequent AOI before the pattern for each group of people. If there are multiple of them, all of them should be printed.
