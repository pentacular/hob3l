rotate([0,0,182])
rotate([0,-90,0]){
    difference(){
        rotate([-45,0,0]) {
            cube([30, 30, 30]);
        }
        scale([1,0.9,0.5]) {
            rotate([-45,0,0]) {
                cube([30, 30, 30]);
            }
        }
    }
}