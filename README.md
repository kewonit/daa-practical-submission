# Design & Analysis of Algorithms Laboratory

**Program:** B. Tech. I.T.  
**Semester:** V  
**Course:** Design & Analysis of Algorithms Laboratory

---

## Practical Problems

### 1. Customer Order Sorting System

**Objective:** Design and implement a sorting algorithm using Merge Sort to efficiently arrange customer orders based on their timestamps.

**Problem Statement:**  
Develop a solution that handles large datasets (up to 1 million orders) with minimal computational overhead. The implementation should efficiently sort customer orders by their timestamps using the Merge Sort algorithm.

**Requirements:**

- Implement Merge Sort algorithm for timestamp-based sorting
- Handle datasets with up to 1 million orders
- Minimize computational overhead
- Analyze time complexity
- Compare performance with traditional sorting techniques

**Expected Analysis:**

- Time complexity analysis of Merge Sort
- Comparison with other sorting algorithms (Quick Sort, Bubble Sort, etc.)
- Performance evaluation on large datasets

---

### 2. Movie Recommendation System Optimization

**Scenario:** StreamFlix OTT Platform  
A popular OTT platform, StreamFlix, offers personalized recommendations by sorting movies based on user preferences, such as IMDB rating, release year, or watch time popularity. However, during peak hours, sorting large datasets slows down the system.

**Role:** Backend Engineer

**Requirements:**

- Implement Quicksort to efficiently sort movies based on various user-selected parameters
- Handle large datasets containing millions of movies while maintaining fast response times
- Support multiple sorting criteria:
  - IMDB rating
  - Release year
  - Watch time popularity

**Objectives:**

- Optimize system performance during peak hours
- Ensure scalability for large movie datasets
- Maintain fast response times for user requests

---

### 3. Emergency Relief Supply Distribution

**Scenario:** Flood Relief Operation  
A devastating flood has hit multiple villages in a remote area, and the government, along with NGOs, is organizing an emergency relief operation. A rescue team has a limited-capacity boat that can carry a maximum weight of W kilograms.

**Role:** Logistics Manager

**Problem Details:**
The boat must transport critical supplies (food, medicine, drinking water) from a relief center to affected villages. Each relief item has:

- **Weight (wi):** in kilograms
- **Utility value (vi):** indicating importance (medicine > food)
- **Divisibility:** Some items can be divided (food, water), others cannot (medical kits)

**Requirements:**

1. Implement the **Fractional Knapsack algorithm** to maximize total utility value
2. Prioritize high-value items while considering weight constraints
3. Allow partial selection of divisible items (e.g., fraction of food packets)
4. Ensure optimal supply distribution given weight limit W

**Expected Outcome:**
Maximize the utility value of supplies transported while respecting the boat's weight capacity.

---

### 4. Smart Traffic Management for Emergency Vehicles

**Scenario:** Intelligent Traffic System for Ambulances  
A smart city is implementing an intelligent traffic management system to assist ambulances in reaching hospitals as quickly as possible.

**Role:** Transportation Engineer

**System Model:**

- **Nodes:** Intersections (junctions)
- **Edges:** Roads with weights representing travel time (considering traffic congestion)
- **Dynamic:** Weights change in real-time based on traffic conditions

**Requirements:**

1. Implement **Dijkstra's algorithm** to find shortest path from ambulance location (S) to all possible hospitals
2. Account for dynamic weight updates as traffic conditions change
3. Optimize for large cities with thousands of intersections and roads
4. Provide visual representation of optimal path for navigation

**Expected Outcome:**
The system should suggest the quickest route for ambulances, updating dynamically based on real-time traffic conditions, ensuring minimal emergency response time.

---

### 5. Multi-Stage Delivery Route Optimization

**Scenario:** SwiftCargo Logistics Company  
SwiftCargo specializes in delivering packages across multiple cities. The company divides the transportation network into multiple stages (warehouses, transit hubs, and final delivery points).

**Role:** Logistics Optimization Engineer

**Network Model:**

- **Structure:** Directed, weighted multistage graph
- **Stages:** N predefined stages (warehouses → transit hubs → delivery points)
- **Constraint:** Every package must pass through at least one node in each stage

**Requirements:**

1. Model transportation network as a directed, weighted multistage graph
2. Implement efficient algorithm (Dynamic Programming or Dijkstra's Algorithm) for optimal delivery routes
3. Scale for large datasets (thousands of cities and routes)
4. Analyze and optimize route selection based on real-time constraints:
   - Traffic conditions
   - Weather delays
   - Fuel efficiency

**Additional Constraints:**

- Multiple paths with different costs/times between stages
- Handle real-time changes (road closures, rerouting)
- Support batch processing for multiple delivery requests

**Expected Outcome:**
Cost-efficient and time-optimized delivery routes that adapt to real-time conditions and scale for large logistics networks.

---

### 6. Disaster Relief Resource Allocation

**Scenario:** Earthquake Relief Operation  
A massive earthquake has struck a remote region, and a relief organization is transporting essential supplies to the affected area. The organization has a limited-capacity relief truck that can carry a maximum weight of W kg.

**Role:** Logistics Coordinator

**Problem Details:**
They have N different types of essential items, each with:

- **Weight (wi):** in kilograms
- **Utility value (vi):** importance in saving lives and meeting urgent needs
- **Indivisibility:** Each item must be either completely included or excluded

**Requirements:**

1. Model this problem using the **0/1 Knapsack approach**, where each item can either be included in the truck (1) or not (0)
2. Implement an algorithm using **Dynamic Programming** to find the optimal set of items that maximizes utility while staying within the weight constraint
3. Analyze the performance of different approaches (e.g., Brute Force, Dynamic Programming, and Greedy Algorithms) for solving this problem efficiently
4. Optimize for real-world constraints, such as perishable items (medicines, food) having priority over less critical supplies

**Extension:**
Extend the model to consider multiple trucks or real-time decision-making for dynamic supply chain management.

**Expected Outcome:**
Maximize the total utility value of supplies transported while ensuring the total weight does not exceed the truck's limit, with priority given to critical items.

---
