<!-- Control web page of MRPi1  -->
<!-- Author : Mace Robotics (www.macerobotics.com) -->
<!-- Version : 0.1  -->
<!-- Simple control : forward, back, turn and stop -->


<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
            <title>Control Web page MRPi1 robot</title>
        <link rel="stylesheet" type="text/css" href="style.css" />
  
    </head>
    
    <body>
	
        <center>
        <h1>Control Web page MRPi1 robot</h1>
            </center>
        <center>
              <form method="get" action="index.php">
				<input type="submit" name="forward" class="fleche_forward"  value="" />
                <br /><br />
                <input type="submit" name="turnLeft" class="fleche_left" value="" />
                <input type="submit" name="stop" class="stop_button" value="" />
                <input type="submit" name="turnRight" class="fleche_right" value="" />
                <br /><br />
				<input type="submit" name="back" class="fleche_back" value="" />
                <br /><br />
                <br /><br />
                Speed control : 
                <br /><br />
				<input id="speed" type="range" value="50" min="0" max="100" name="speed" style="width:200px"">
               </form>
        </center>
      </form>
	  
       <?php

             // Move forward
         if(isset($_GET['forward']))
         {
		
		   $cmd = "echo '#MF," . $_GET['speed'] . "!' > /dev/ttyAMA0"; 
		   exec($cmd);
		   
		   
         }
             
         // turn left
         if(isset($_GET['turnLeft']))
         {
		   $cmd = "echo '#TL," . $_GET['speed'] . "!' > /dev/ttyAMA0"; 
           exec($cmd);
		   
         }
             
          // stop
          if(isset($_GET['stop']))
          {
            $cmd = "echo '#STP!' > /dev/ttyAMA0";
			exec($cmd);

          }
             
          // turn right
          if(isset($_GET['turnRight']))
          {
            $cmd = "echo '#TR," . $_GET['speed'] . "!' > /dev/ttyAMA0"; 
			exec($cmd);
			
          }
             
          // Move back
          if(isset($_GET['back']))
          {
            $cmd = "echo '#MB," . $_GET['speed'] . "!' > /dev/ttyAMA0"; 
			exec($cmd);
			
          }

      ?>
    
        
                  <br /><br /> 
                  <center>
                    <a href="http://www.macerobotics.com">www.macerobotics.com</a>
                  </center>
    </body>
</html>