# Indexing-Tweets

## Requirements
In this assignment, you are given a list of tweets in an external text file called “tweets.txt”. In this text file, you can find a number of real tweets extracted from Twitter1. In these days, most of the tweets include a hashtag2 which start with the # character. For example #programming hashtag can be used by somebody who sends a tweet related to programming and then when somebody else also sends a tweet with the same hashtag, these tweets are grouped together.

In this assignment, we want to process the given tweets and find out the hashtags used in these tweets and index these tweets given these hashtags. In order to create such index, we will process these tweets and whenever we find a hashtag (i.e., a text which starts with the # character and finishes with a space), we will add that hashtag to the AVL tree and we will also record the tweet id. For example, when we process the first tweet (first line), which has the following tweet:
* Build a Website by amith7951 https://t.co/eoW5q7V2Fh #net #ajax #asp #cprogramming #sql

We will add “net” “ajax” “asp” “cprogramming” and “sql” to the AVL tree and for each node we will also record the tweet id 1. After that, when we process the second tweet:
* Program Entirely with Static Methods. Great post from @mikehadlow https://t.co/qzTxx6c22t #cprogramming #coding

We will need to record “cprogramming” and “coding” but “cprogramming” is already recorded so we will only add tweet id 2 to this node in the tree, and we will insert “coding” to the AVL tree. In summary, after we process the first two tweets, our AVL tree will look like this.
<p align="center"><img src="https://i.ibb.co/PMGmzfv/image-2022-09-10-195146973.png"></p>
Once you finish indexing the tweets in the document, then you will display the index of the tweets by using the AVL tree. You will need to display all the hashtags indexed in the alphabetical order. For example, for the given AVL tree above, you will display the following:

    ajax (Tweets: 1)
    asp (Tweets: 1)
    coding (Tweets: 2)
    cprogramming (Tweets: 1, 2)
    net (Tweets: 1)
    sql (Tweets: 1)
  
We assume that "#" will only be used for hashtags. If there is no hashtag in a tweet, then there will no "#" in the tweet.

## Programming Requirements
You will start this programming by taking the file name as a command line input and then you will need to implement at least the following functions:
* **read_tweet_data:** This function will mainly process the external file. As an input, it will take the file name and it will return an AVL tree.
* **insert_hashtag:** This function will take an AVL tree, a hashtag, and the tweet id and it will try to insert it to the AVL tree. If it is already in the tree, then it will update the existing node with the tweet id (you cannot again make assumptions about the number of tweets here, so make sure that you use a dynamic list - you are encouraged to use a linked list here), if it is not then it will create a new node and add it to the tree. Please note that the tree will not be case-sensitive. For example, #PROGRAMMING and #programming will be considered as the same hashtag.
* **display_index:** This function will mainly take an AVL tree and display the index of the tweets in an alphabetical order.
* **display_the_most_trending_hashtag:** This function will mainly take an AVL tree and will find the hashtag with the maximum number of tweets. If there is more than one hashtag with the maximum number of tweets, all of them should be displayed. In the comment part of this function, discuss the complexity of this function based on your current representation of data. You also need to discuss if there is a way you could improve this.
* **main:** The main function is responsible from coordinating all the functions. There will be a menu which allows to display the index and the most trending hashtag, and to exit from the program.
Please note that in this assignment, you can make use of the functions in the string.h library and similar external libraries. You cannot make an assumption about the number of tweets in this external file. Please also note that your solution should be able to take any file in the given format and be able to create the index.
