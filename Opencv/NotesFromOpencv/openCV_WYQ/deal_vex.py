import numpy


def deal(contours):
    if isinstance(contours, list):
        lines = []
        for val in contours:
            if isinstance(val, numpy.ndarray):

                pos = []
                vals = [[], []]
                fx = []
                for poses in val:
                    poses = poses[0]
                    if not vals[0]:
                        vals[0] = list(poses)
                    else:
                        xf = poses[0] - vals[0][0]
                        yf = poses[1] - vals[0][1]
                        if not fx:
                            fx = [xf, yf]
                            vals[1] = list(poses)
                        else:
                            if xf in range(fx[0] - 6, fx[0] + 6) and yf in range(fx[1] - 6, fx[1] + 6):
                                vals[1] = list(poses)
                            else:
                                pos.append(vals)
                                vals = [[], []]
                                fx = []

                    print(pos)

                lines.append(pos)
        return lines


def find_roi(contours):
    rois = []
    for val in contours:
        rect = [0,  # x
                0,  # y
                1,  # w+x
                1  # h+y
                ]
        posees = list(zip(*val))[0]
        x_group, y_group = list(zip(*posees))
        rect = [min(x_group), min(y_group), max(x_group), max(y_group)]

        rois.append(rect)
    return rois
