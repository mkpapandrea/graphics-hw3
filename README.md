1. Predator
I made the predator slightly larger than the flockers and white. this was both for testing purposes and for contrast. To draw it, i used similar code to the flockers and just modified the main to make it appear.

2. hunger_force
the hunger force is defined in the update function in predator. my hungerforce was computed suing the difference in position to the flocker array and then normalizing it to the flocker array. Just using the hungerforce made the predator very twitchy so i weighted the current acceleration and the hungerforce together to make it smoother. (90% acceleration, 10% hunger force seemed like the smoothest ratio)

3. fear_force
the fear force was computed in tha same way as the hunger force except it took the difference of and normalized with one predator. The flockers only ran away if the difference between them was less than 2