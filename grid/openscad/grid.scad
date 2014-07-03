number_cells_horizontal = 12;
number_cells_vertical = 12;


cell_size = 33; // width and length of one grid cell
grid_height = cell_size; // height of the grid

led_width = 5; // Size of the hole for the LED chips
led_height = 5;

bottom_grid_connect_width = 10;
bottom_thickness = 3;

grid_thickness = 3;

joint_size = 0.2; // size to extend the holes with to allow easier assembling


bottom_width = cell_size*number_cells_horizontal+grid_thickness;
bottom_height = cell_size*number_cells_vertical+grid_thickness;

led_offset_x = (cell_size/2+led_width/2)-grid_thickness/2;
led_offset_y = (cell_size/2+led_width/2)-grid_thickness/2;

module bottomPlate(){
  difference() {
    cube([bottom_width, bottom_height, bottom_thickness]); 
   
    for(x=[1:number_cells_horizontal]) {
      for(y=[1:number_cells_vertical]) {
        translate([x*cell_size-led_offset_x,y*cell_size-led_offset_y,-1])
          cube([led_width,led_height,bottom_thickness+2]);
      }
    } 
    for(x=[1:number_cells_horizontal]) {
      for(y=[0:number_cells_vertical]) {
       translate([x*cell_size+(grid_thickness-joint_size)/2-(cell_size-bottom_grid_connect_width)/2-bottom_grid_connect_width,y*cell_size-joint_size/2,-1])
        cube([bottom_grid_connect_width+joint_size,grid_thickness+joint_size,bottom_thickness+2]);
      }
    }
    for(x=[1:number_cells_horizontal]) {
      for(y=[0:number_cells_vertical]) {
       rotate([0,0,90])
       translate([x*cell_size+(grid_thickness-joint_size)/2-(cell_size-bottom_grid_connect_width)/2-bottom_grid_connect_width,-y*cell_size-grid_thickness-joint_size/2,-1])
        cube([bottom_grid_connect_width+joint_size,grid_thickness+joint_size,bottom_thickness+2]);
      }
    }
  }
}

module partA() {
  difference() {
    cube([bottom_width,grid_height+bottom_thickness,grid_thickness]);
    for(x=[0:number_cells_horizontal]) {
      translate([x*cell_size-joint_size/2,grid_height/2+bottom_thickness,-1])
        cube([grid_thickness+joint_size,grid_height/2+1,grid_thickness+2]);
    }
    for(x=[0:number_cells_horizontal]) {
      translate([x*cell_size+grid_thickness/2-(cell_size-bottom_grid_connect_width)/2,0,-1])
        cube([cell_size-bottom_grid_connect_width,bottom_thickness,grid_thickness+2]);
    }
  }
}


module partB() {
  difference() {
    cube([bottom_width,grid_height+bottom_thickness,grid_thickness]);
    for(x=[0,number_cells_horizontal]) {
      translate([x*cell_size-joint_size/2,grid_height/2+bottom_thickness,-1])
        cube([grid_thickness+joint_size,grid_height/2+1,grid_thickness+2]);
    }
    for(x=[1:number_cells_horizontal-1]) {
      translate([x*cell_size-joint_size/2,bottom_thickness-1,-1])
        cube([grid_thickness+joint_size,grid_height/2+1,grid_thickness+2]);
    }
    for(x=[0:number_cells_horizontal]) {
      translate([x*cell_size+grid_thickness/2-(cell_size-bottom_grid_connect_width)/2,0,-1])
        cube([cell_size-bottom_grid_connect_width,bottom_thickness,grid_thickness+2]);
    }
  }
}

module partC() {
  difference() {
    cube([bottom_width,grid_height+bottom_thickness,grid_thickness]);
    for(x=[0:number_cells_horizontal]) {
      translate([x*cell_size-joint_size/2,bottom_thickness-1,-1])
        cube([grid_thickness+joint_size,grid_height/2+1,grid_thickness+2]);
    } 
    for(x=[0:number_cells_horizontal]) {
      translate([x*cell_size+grid_thickness/2-(cell_size-bottom_grid_connect_width)/2,0,-1])
        cube([cell_size-bottom_grid_connect_width,bottom_thickness,grid_thickness+2]);
    }
  }
}

/* 
 * Uncomment to check for intersections
 */
/*
intersection() {
  difference() {
    bottomPlate();

    for(x=[1:number_cells_horizontal-1]) {
      translate([0,x*cell_size+grid_thickness,0])
        rotate([90,0,0])
          partA();
    }

    for(x=[0:number_cells_horizontal]) {
      translate([x*cell_size,0,0])
        rotate([90,0,90])
          partB();
    }

    for(x=[0,number_cells_horizontal]) {
      translate([0,x*cell_size+grid_thickness,0])
        rotate([90,0,0])
          partC();
    }
  }
}
*/


/*
 * Uncomment to render bottom plate
 */
//  projection() bottomPlate();


/*
 * Uncomment to render partA and partC
 */
/*
  projection()  
    for(x=[1:number_cells_horizontal-1]) {
      translate([0,x*(cell_size+5),0])
          partA();
    }
  projection()
    for(x=[0,number_cells_horizontal]) {
      translate([0,x*(cell_size+5),0])
          partC();
    }
*/

/*
 * Uncomment to render partB
 */
/*
  projection()  
    for(x=[0:number_cells_horizontal]) {
      translate([0,x*(cell_size+5),0])
          partB();
    }
*/

