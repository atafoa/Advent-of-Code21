with open('input.txt') as fi:
    a = [[int(x) for x in lines[:-1]] for lines in fi.readlines()]

height = len(a)
width = len(a[0])

def compare(r,c):
    dr = [1,0,-1,0]
    dc = [0,1,0,-1]
    lowpoint = True
    for i in range(4):
        rr,cc = r+dr[i],c+dc[i]
        if rr>=0 and cc >= 0 and rr < height and cc < width:
            if a[r][c] >= a[rr][cc]: lowpoint = False
    return lowpoint

lowpoints = set()
def main1():
    risklvl = 0
    for r in range(height):
        for c in range(width):
            if compare(r,c):
                lowpoints.add((r,c))
                risklvl += 1 + a[r][c]
    print(lowpoints)
    print(" ")
    print("Solution 1:", risklvl)
    print(" ")
    


def compare_rek(r,c,basin):
    dr = [1,0,-1,0]
    dc = [0,1,0,-1]
    newpoints = set()
    for i in range(4):
        rr,cc = r+dr[i],c+dc[i]
        if (rr,cc) not in basin and rr>=0 and cc >= 0 and rr < height and cc < width and a[rr][cc]<9:
                newpoints.add((rr,cc))
    basin = basin.union(newpoints)
    for np in newpoints:
        basin = basin.union(compare_rek(np[0],np[1],basin))
    return basin

def main2(): # main for part 2 with recursion  / corrected version... because:
    #all other locations will always be part of exactly one basin. 
    basins = []
    for r,c in lowpoints:
        basins += [len(compare_rek(r,c,set({(r,c)})))]
    prod = 1
    for i in range(3):
        maximum = max(basins)
        basins.remove(maximum)
        print(maximum)
        prod *=maximum
    print(" ")
    print("Solution :", prod)
    print(" ")
    
print('----Part 1----')
main1()
print('----Part 2----')
main2()
