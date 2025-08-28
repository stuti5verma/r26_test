MotionCommand Odometry::computeCommands(vector<pair<int, int>> &path) {
    MotionCommand res = {0.0, 0.0}; // total time (sec), final orientation (deg)

    if (path.size() < 2)
        return res; // no movement if path is empty or has only one point

    double total_time = 0.0;
    double last_angle = 0.0;

    for (size_t i = 0; i < path.size() - 1; i++) {
        int x1 = path[i].first, y1 = path[i].second;
        int x2 = path[i + 1].first, y2 = path[i + 1].second;

        // 1. Distance between consecutive points
        double d = distance(x1, y1, x2, y2);

        // 2. Time = distance / linear velocity
        double t = d / linear_vel;
        total_time += t;

        // 3. Orientation (angle to next point)
        last_angle = angle(x1, y1, x2, y2);
    }

    res.time_sec = total_time;
    res.angle_deg = last_angle; // final orientation after completing path
    return res;
}
