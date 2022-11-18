# **Seam Carving**
Seam carving is an algorithm for content-aware image resizing, developed by Shai Avidan, of Mitsubishi Electric Research Laboratories (MERL), and Ariel Shamir, of the Interdisciplinary Center and MERL. It functions by establishing a number of seams (paths of least importance) in an image and automatically removes seams to reduce image size or inserts seams to extend it.

## **Seams**
Can be either vertical or horizontal. A **vertical seam** is a path of pixels connected from top to bottom in an image with one pixel in each row. A **horizontal seam** is similar with the exception of the connection being from left to right. The importance/energy function values a pixel by measuring its contrast with its neighbor pixels.

## **Objective**
This project seeks to calculate the energy of an image, as well as to find both the horizontal and vertical paths of the pixels that have less importance in the image, and then be eliminated. Generating a new image without those pixels.

#### **Note**
If you wish to test this code, you will need to install (if you have not already done so) the C++ compiler. You can do this by running the following commands in your terminal:

```
sudo apt update
sudo apt install gcc libncurses5-dev build-essential
```
You may also need to install the following package:

```
sudo apt install libpng-dev
```

## **Examples**
In this project there are two images in the resources folder: *`arch.png`* and *`surfer.png`*. In the examples shown below, *`surfer.png`* will be used. You can use arch.png or any other image you wish.

<p align="center">
  <img src="https://user-images.githubusercontent.com/97962412/202604067-7d5d04d2-efa8-42eb-8492-e9023c77035c.png" alt="surfer" />
</p>

* ## **Image Energy**
This method is used to obtain the pixels that have the greatest difference in RGB colors with respect to other pixels. In other words, the most important pixels of the image are obtained.

By executing the following command, the energy of the image used in this example is obtained:

```
make main; ./main/bin/ImageEnergy resources/surfer.png
```

Generating the following image:

<p align="center">
  <img src="https://user-images.githubusercontent.com/97962412/202606679-2219ba70-45a9-43ed-ab77-e93c9300e59e.png" alt="surfer-energy" />
</p>

* ## **Minimum Vertical Seam**
This method is used to find the lowest energy vertical seam given the energy of each pixel in the input image. That is, it returns an image with the lowest energy pixel accumulated at the bottom of the image.

To do so, the following command is executed:

```
make main; ./main/bin/MinVerticalSeam resources/surfer.png
```
As a result, the following image is obtained:

<p align="center">
  <img src="https://user-images.githubusercontent.com/97962412/202607824-424249f8-a6f2-4fac-9d38-1158c2e5565b.png" alt="surfer-vertical-seam" />
</p>

* ## **Vertical Seam**
This method is responsible for drawing a path from the top of the image to the bottom that indicates the vertical pixels that are less important in the image.

To do this, the following command is executed:

```
make main; ./main/bin/VerticalSeam resources/surfer.png
```

Resulting in the following image:

<p align="center">
  <img src="https://user-images.githubusercontent.com/97962412/202608984-be1fd957-fe0d-4533-affa-809188d4ac1e.png" alt="surfer-vertical-seams" />
</p>

* ## **Vertical Seam Carving**
In this last method for the case of vertical seams, the objective is to remove `n` number of vertical seams according to the supplied input. In this example, `n = 1200`, which means that from the original image, the least relevant `1200` vertical seams will be removed from the original image.

To do this, run the following command:

```
make main; ./main/bin/VerticalSeamCarving resources/surfer.png 1200
```

And the result is the following image:

<p align="center">
  <img src="https://user-images.githubusercontent.com/97962412/202610266-ce199603-3170-4da4-9769-65f2ff090d1d.png" alt="surfer-vertical-resized-1200" />
</p>

* ## **Minimum Horizontal Seam**
Unlike Minimum Vertical Seam, this method is used to find the lowest energy horizontal seam given the energy of each pixel in the input image. That is, it returns an image with the pixel with the lowest energy accumulated in the right part of the image.

To do this, the following command is executed:

```
make main; ./main/bin/MinHorizontalSeam resources/surfer.png
```
This produces the following image as a result:

<p align="center">
  <img src="https://user-images.githubusercontent.com/97962412/202749536-b55d0c49-4fec-4b23-ae29-065cf33aa59e.png" alt="surfer-horizontal-seam" />
</p>

* ## **Horizontal Seam**
In this case, the objective of this method is to draw a path from the left part of the image to the right part that indicates the least important horizontal pixels of the image.

To achieve this, the following line is executed:

```
make main; ./main/bin/HorizontalSeam resources/surfer.png
```

And the following image is generated:

<p align="center">
  <img src="https://user-images.githubusercontent.com/97962412/202761837-64eeae98-e456-4543-9480-485b6706c48a.png" alt="surfer-horizontal-seams" />
</p>

* ## **Horizontal Seam Carving**
In this last method for the case of horizontal seams, the objective is to remove `n` number of horizontal seams based on the supplied input. In this example, `n = 800`, which means that from the original image, the least relevant `800` horizontal seams will be removed from the original image.

To do this, run the following command:

```
make main; ./main/bin/HorizontalSeamCarving resources/surfer.png 800
```

This image is the result:

<p align="center">
  <img src="https://user-images.githubusercontent.com/97962412/202763188-61b59731-0f68-4127-90c7-775ab87b01b2.png" alt="surfer-horizontal-resized-800" />
</p>

* ## **Mixing Vertical Seam Carving with Horizontal Seam Carving**
After executing the command:

```
make main; ./main/bin/VerticalSeamCarving resources/surfer.png 1200
```

An image named *`surfer-vertical-resized-1200.png`* is generated with the vertical seams removed (it's the same image obtained from Vertical Seam Carving). Then, by running the following line:

```
make main; ./main/bin/HorizontalSeamCarving resources/surfer-vertical-resized-1200.png 800
```

The following image is obtained:

<p align="center">
  <img src="https://user-images.githubusercontent.com/97962412/202766646-590b1309-121c-4cc9-9556-5685ee02ab7b.png" alt="surfer-vertical-resized-1200-horizontal-resized-800" />
</p>

And in this way, from the *`surfer.png`* image, the `1200` less important vertical seams have been removed from the image, as well as the `800` less relevant horizontal seams.