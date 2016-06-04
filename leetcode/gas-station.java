// There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
// You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i// +1). You begin the journey with an empty tank at one of the gas stations.
// Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

public class Solution {
    public int canCompleteCircuit(int[] gas, int[] cost) {
        
        if (gas==null) return -1;
        
        int[] diff=new int[gas.length];
        for (int i=0;i<gas.length;i++){
            diff[i]=gas[i]-cost[i];
        }
        
        int remain=diff[0];
        int start=0;
        int end=0;
        int count=0;
        
        while (start!=end || count==0) {
            count++;
            if (remain>=0) {
                start=(start+1)%diff.length;
                remain+=diff[start];
            }
            else {
                end=(end+diff.length-1)%diff.length;
                remain+=diff[end];
            }
            
        }
        
        if (remain>=0) return end;
        else return -1;
        
    }
}
