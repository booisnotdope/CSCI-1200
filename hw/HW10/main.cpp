#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <set>

#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double distance(const DistancePixel& a, const DistancePixel& b);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations 
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
	for (int j2 = 0; j2 < h; j2++) {
	  const Color& c = input.GetPixel(i2,j2);      
	  // skip all pixels that are not black
	  if (!c.isBlack()) continue;
	  // calculate the distance between the two pixels
	  double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
	  // store the closest distance to a black pixel
	  if (closest < 0 || distance < closest) {
	    closest = distance;
	  }
	}
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}


double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  //vector of black pixels
  std::vector<DistancePixel> vec_black;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      //only check if the pixel is black or not
      Color& c = input.GetPixel(i,j);
      if (c.isBlack()){ 
        //create a DistancePixel class and set its x and y
        DistancePixel b = distance_image.GetPixel(i,j);
        b.setX(i); b.setY(j);
        vec_black.push_back(b);
      }
    }
  }

  //now run through the entire picture again
  for (int i2 = 0; i2 < w; i2++)  {
    for (int j2 = 0; j2 < h; j2++) {
      double closest = -1;
      for (DistancePixel c: vec_black){
        // calculate the distance between the two pixels
        double distance = sqrt((i2-c.getX())*(i2-c.getX()) + 
                                (j2-c.getY())*(j2-c.getY()));
        // store the closest distance to a black pixel
        if (closest < 0 || distance < closest) closest = distance;
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i2,j2);
      p.setValue(closest);
      
    }
  }
  //returns the largest distance
  return answer;
}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  std::set<DistancePixel*> pixels_seen;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      //only check if the pixel is black or not
      Color& c = input.GetPixel(i,j);
      if (c.isBlack()){ 
        //create a DistancePixel class and set its x and y
        DistancePixel* b = &distance_image.GetPixel(i,j);
        (*b).setX(i); (*b).setY(j); (*b).setValue(0);
        pixels_seen.insert(b);
      } else {
        DistancePixel& p = distance_image.GetPixel(i, j);
        p.setX(i); p.setY(j); p.setValue(696969);
      }
    }
  }
  
  //puts all black pixels into a priotiry q
  DistancePixel_PriorityQueue q;
  for (DistancePixel* b: pixels_seen){
    q.push(b);
  }

  //goes through the entire queue and checks the distance between 
  double max_dist = 0;
  while(!q.empty()){
    const DistancePixel* p = q.top();
    q.pop(); 
    DistancePixel* new_p = const_cast<DistancePixel*> (p);
    pixels_seen.insert(new_p);
    int x_pos = new_p -> getX();
    int y_pos = new_p -> getY();
    int dist = new_p -> getValue();

    //goes through the popped pixel's neighbors. first check if
    //the neighbor is in bounds
    for(int i = -1; i < 1; i++){
      int neighbor_x = i + x_pos;
      if (neighbor_x < 0 || neighbor_x >= w) continue;
      for(int j = -1; j < 1; j++){
        int neighbor_y = j + y_pos;
        if (neighbor_y < 0 || neighbor_y >= h) continue;
        //if the neighbor is black just skip it
        if (input.GetPixel(neighbor_x, neighbor_y).isBlack()) continue;
        //find the neighbor in the image and calculate the distance
        //between the black pixel and the neighbor pixel
        DistancePixel& n = distance_image.GetPixel(neighbor_x, neighbor_y);
        if (pixels_seen.find(&n) != pixels_seen.end()) continue;
        double n_dist = dist + distance(n, *new_p);
          max_dist = std::max(max_dist, n_dist);
        //check if it already is in the heap
        if(q.in_heap(&n)){
          //check if the n_dist is smaller than the original dist
          if (n_dist < n.getValue()){
            n.setValue(n_dist); 
            q.update_position(&n);
          }
        } else {
          q.push(&n);
        }
      }
    }
  }
  return max_dist;
}

//find the distance between 2 pixels
double distance(const DistancePixel& a, const DistancePixel& b){
  return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + 
              (a.getY() - b.getY()) * (a.getY() - b.getY()));
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }  
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }  
  return answer;
}

// ===================================================================================================
