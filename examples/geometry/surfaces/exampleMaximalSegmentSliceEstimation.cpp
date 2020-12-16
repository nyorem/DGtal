/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file
 * @ingroup Examples
 * @author Jocelyn Meyron (\c jocelyn.meyron@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2020/12/15
 *
 * An example file named exampleMaximalSegmentSliceEstimation.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
#include "DGtal/geometry/surfaces/estimation/MaximalSegmentSliceEstimation.h"
#include "DGtal/helpers/Shortcuts.h"
#include "DGtal/io/viewers/Viewer3D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

using KSpace    = Z3i::KSpace;
using SH3       = Shortcuts<KSpace>;
using Surface   = SH3::DigitalSurface;
using Surfel    = Surface::Surfel;
using Estimator = MaximalSegmentSliceEstimation<Surface>;
using Quantity  = Estimator::Quantity;
using RealPoint = SH3::RealPoint;
using Point     = SH3::Point;

RealPoint centerSurfel (KSpace const& K, SH3::SCell const& s)
{
    auto pointels = SH3::getPrimalVertices(K, s, true);

    Point p = K.uCoords(pointels[0]),
          u = K.uCoords(pointels[1]) - p,
          v = K.uCoords(pointels[3]) - p;

    static const RealPoint shift(-0.5, -0.5, -0.5);

    return p + 0.5 * u + 0.5 * v + shift;
}

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    QApplication application(argc, argv);

    auto params = SH3::defaultParameters();
    params("polynomial", "goursat")("gridstep", "1.0");
    auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto K               = SH3::getKSpace( params );
    auto binary_image    = SH3::makeBinaryImage( digitized_shape, params );
    auto surface         = SH3::makeDigitalSurface( binary_image, K, params );
    auto surfels         = SH3::getSurfelRange(surface);

    double gridstep = params["gridstep"].as<double>();

    Viewer3D<> viewer(K);
    viewer << SetMode3D(Surfel().className(), "Basic");
    viewer.show();

    Estimator estimator(surface);
    estimator.init(gridstep, surfels.begin(), surfels.end());
    estimator.attach(surface);

    std::vector<Quantity> quantities;
    estimator.eval(surfels.begin(), surfels.end(), std::back_inserter(quantities));

    Color fillColor = viewer.getFillColor();

    for (std::size_t i = 0; i < surfels.size(); ++i)
    {
        const Surfel& s = surfels[i];
        const Quantity& n = quantities[i];

        RealPoint origin = centerSurfel(K, s);

        viewer.setFillColor(fillColor);
        viewer << s;

        viewer.setLineColor(Color::Green);
        viewer.addLine(origin, origin + 1.5 * n, 0.3);
    }

    viewer << Viewer3D<>::updateDisplay;
    application.exec();

    return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////