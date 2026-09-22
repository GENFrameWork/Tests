/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_UIScale.cpp
*
* @brief      UserInterface unit tests for UIScale (design canvas + scale contract)
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_UIScale.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_Layout.h"
#include "UI_StyleSheet.h"
#include "UI_BoundaryLine.h"
#include "UI_Element.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_UISCALE
{


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, DefaultsAreUnsetDesignScaleOneInactive)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  EXPECT_EQ(layout.GetDesignWidth(),  (XDWORD)0);
  EXPECT_EQ(layout.GetDesignHeight(), (XDWORD)0);
  EXPECT_DOUBLE_EQ(layout.GetUIScale(), UI_LAYOUT_UISCALE_DEFAULT);
  EXPECT_FALSE(layout.GetUIScaleEnabled());
  EXPECT_FALSE(layout.IsUIScaleActive());
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, DesignSizeAndScaleRoundTrip)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  layout.SetDesignSize(1440, 900);
  layout.SetUIScale(1.0);

  EXPECT_EQ(layout.GetDesignWidth(),  (XDWORD)1440);
  EXPECT_EQ(layout.GetDesignHeight(), (XDWORD)900);
  EXPECT_DOUBLE_EQ(layout.GetUIScale(), 1.0);

  layout.SetUIScale(1.5);
  EXPECT_DOUBLE_EQ(layout.GetUIScale(), 1.5);

  layout.SetDesignSize(0, 0);
  EXPECT_EQ(layout.GetDesignWidth(),  (XDWORD)0);
  EXPECT_EQ(layout.GetDesignHeight(), (XDWORD)0);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, SetUIScaleClampsNonPositive)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  layout.SetUIScale(0.0);
  EXPECT_DOUBLE_EQ(layout.GetUIScale(), UI_LAYOUT_UISCALE_MIN);

  layout.SetUIScale(-2.0);
  EXPECT_DOUBLE_EQ(layout.GetUIScale(), UI_LAYOUT_UISCALE_MIN);

  layout.SetUIScale(UI_LAYOUT_UISCALE_MIN);
  EXPECT_DOUBLE_EQ(layout.GetUIScale(), UI_LAYOUT_UISCALE_MIN);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, SetUIScaleClampsToProductMax)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  layout.SetUIScale(3.0);
  EXPECT_DOUBLE_EQ(layout.GetUIScale(), UI_LAYOUT_UISCALE_MAX);

  layout.SetUIScale(UI_LAYOUT_UISCALE_MAX);
  EXPECT_DOUBLE_EQ(layout.GetUIScale(), UI_LAYOUT_UISCALE_MAX);

  layout.SetUIScale(1.25);
  EXPECT_DOUBLE_EQ(layout.GetUIScale(), 1.25);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, ComputeFitUIScaleIsMinOfAxes)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);
  layout.SetDesignSize(1440, 900);

  // Exact half: min(720/1440, 450/900) = 0.5
  EXPECT_NEAR(layout.ComputeFitUIScale(720, 450), 0.5, 1e-9);

  // Wider window, height-limited: min(1920/1440, 900/900) = 1.0
  EXPECT_NEAR(layout.ComputeFitUIScale(1920, 900), 1.0, 1e-9);

  // Tall window, width-limited: min(1440/1440, 1200/900) = 1.0
  EXPECT_NEAR(layout.ComputeFitUIScale(1440, 1200), 1.0, 1e-9);

  // Same aspect larger: min(2880/1440, 1800/900) = 2.0 (at MAX)
  EXPECT_NEAR(layout.ComputeFitUIScale(2880, 1800), 2.0, 1e-9);

  // Above MAX clamps
  EXPECT_NEAR(layout.ComputeFitUIScale(4000, 3000), UI_LAYOUT_UISCALE_MAX, 1e-9);

  // Below FIT_MIN clamps
  EXPECT_NEAR(layout.ComputeFitUIScale(100, 100), UI_LAYOUT_UISCALE_FIT_MIN, 1e-9);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, SetUIScaleClearsDoesNotAffectFitClamp)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);
  layout.SetUIScaleAutofit(true);
  layout.SetUIScaleForFit(0.5);
  EXPECT_TRUE(layout.GetUIScaleAutofit());
  EXPECT_NEAR(layout.GetUIScale(), 0.5, 1e-9);

  layout.SetUIScale(1.25); // product path — leaves autofit flag alone (manager clears it)
  EXPECT_NEAR(layout.GetUIScale(), 1.25, 1e-9);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, ExplicitFlagActivatesWithoutStylesheet)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  EXPECT_FALSE(layout.IsUIScaleActive());

  layout.SetUIScaleEnabled(true);
  EXPECT_TRUE(layout.GetUIScaleEnabled());
  EXPECT_TRUE(layout.IsUIScaleActive());

  layout.SetUIScaleEnabled(false);
  EXPECT_FALSE(layout.IsUIScaleActive());
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, StylesheetActivatesWithoutExplicitFlag)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  EXPECT_FALSE(layout.IsUIScaleActive());

  UI_STYLESHEET* sheet = new UI_STYLESHEET();
  layout.SetStyleSheet(sheet);

  EXPECT_FALSE(layout.GetUIScaleEnabled());
  EXPECT_TRUE(layout.IsUIScaleActive());
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, XmlOnlyLayoutStaysInactiveLikeUI_Options)
{
  // Smoke for roadmap 1.2: no stylesheet + no explicit flag => legacy geometry path.
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  layout.SetDesignSize(800, 600);
  layout.SetUIScale(1.25);

  EXPECT_FALSE(layout.IsUIScaleActive());
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, ScreenToDesignAndDesignToScreenRoundTrip)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);
  layout.SetUIScaleEnabled(true);
  layout.SetDesignSize(1440, 900);

  const double scales[] = { 1.0, 1.5, 2.0 };
  for(int i = 0; i < 3; i++)
    {
      layout.SetUIScale(scales[i]);
      layout.ComputePresentTransform(1440, 900);

      double sx = 0.0;
      double sy = 0.0;
      layout.DesignToScreen(105.0, 150.0, sx, sy);

      double dx = 0.0;
      double dy = 0.0;
      layout.ScreenToDesign(sx, sy, dx, dy);
      EXPECT_NEAR(dx, 105.0, 1e-9);
      EXPECT_NEAR(dy, 150.0, 1e-9);
    }
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, LetterboxOffsetsCenterWhenScaleBelowOne)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);
  layout.SetUIScaleEnabled(true);
  layout.SetDesignSize(1440, 900);
  layout.SetUIScale(0.75);
  layout.ComputePresentTransform(1440, 900);

  // present = 1080 x 675 → offset (180, 112.5)
  EXPECT_NEAR(layout.GetUIScaleOffsetX(), 180.0, 1e-6);
  EXPECT_NEAR(layout.GetUIScaleOffsetY(), 112.5, 1e-6);

  double dx = 0.0;
  double dy = 0.0;
  layout.ScreenToDesign(180.0 + 105.0 * 0.75, 112.5 + 150.0 * 0.75, dx, dy);
  EXPECT_NEAR(dx, 105.0, 1e-6);
  EXPECT_NEAR(dy, 150.0, 1e-6);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, NeedsScaledPresentWhenScaleNotOne)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);
  layout.SetUIScaleEnabled(true);
  layout.SetDesignSize(1440, 900);
  layout.SetUIScale(1.0);

  EXPECT_FALSE(layout.NeedsScaledPresent(1440, 900));

  layout.SetUIScale(1.5);
  EXPECT_TRUE(layout.NeedsScaledPresent(1440, 900));
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, ScreenToDesignMapsScaledClickOntoDesignHitBox)
{
  // Zoom 1.5: top-left present (sidebar stays on-screen). CPU design (105,150) → screen (157.5, 225).
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);
  layout.SetUIScaleEnabled(true);
  layout.SetDesignSize(1440, 900);
  layout.SetUIScale(1.5);
  layout.ComputePresentTransform(1440, 900);

  EXPECT_NEAR(layout.GetUIScaleOffsetX(), 0.0, 1e-9);
  EXPECT_NEAR(layout.GetUIScaleOffsetY(), 0.0, 1e-9);

  UI_BOUNDARYLINE bline;
  bline.x      = 0.0;
  bline.y      = 174.0;
  bline.width  = 210.0;
  bline.height = 48.0;

  double sx = 0.0;
  double sy = 0.0;
  layout.DesignToScreen(105.0, 150.0, sx, sy);
  EXPECT_NEAR(sx, 157.5, 1e-6);
  EXPECT_NEAR(sy, 225.0, 1e-6);

  double dx = 0.0;
  double dy = 0.0;
  layout.ScreenToDesign(sx, sy, dx, dy);

  EXPECT_TRUE(bline.IsWithin((XDWORD)(dx + 0.5), (XDWORD)(dy + 0.5)));
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, ElementAABBUnchangedWhenOnlyScaleChanges)
{
  // Roadmap 2.3: layout/hit AABB stay in design px — changing scale must not rewrite geometry.
  UI_ELEMENT element;
  element.GetBoundaryLine()->x      = 238.0;
  element.GetBoundaryLine()->y      = 460.0;
  element.GetBoundaryLine()->width  = 376.0;
  element.GetBoundaryLine()->height = 390.0;

  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);
  layout.SetUIScaleEnabled(true);
  element.SetLayout(&layout);

  const double ax = element.GetBoundaryLine()->x;
  const double ay = element.GetBoundaryLine()->y;
  const double aw = element.GetBoundaryLine()->width;
  const double ah = element.GetBoundaryLine()->height;

  layout.SetUIScale(1.0);
  layout.SetUIScale(1.5);
  layout.SetUIScale(2.0);
  layout.SetUIScale(1.0);

  EXPECT_DOUBLE_EQ(element.GetBoundaryLine()->x,      ax);
  EXPECT_DOUBLE_EQ(element.GetBoundaryLine()->y,      ay);
  EXPECT_DOUBLE_EQ(element.GetBoundaryLine()->width,  aw);
  EXPECT_DOUBLE_EQ(element.GetBoundaryLine()->height, ah);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, MinHitSizeDefaultAndDisable)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  EXPECT_DOUBLE_EQ(layout.GetMinHitSize(), UI_LAYOUT_MINHITSIZE_DEFAULT);

  layout.SetMinHitSize(UI_LAYOUT_MINHITSIZE_DISABLED);
  EXPECT_DOUBLE_EQ(layout.GetMinHitSize(), 0.0);

  layout.SetMinHitSize(-10.0);
  EXPECT_DOUBLE_EQ(layout.GetMinHitSize(), 0.0);

  layout.SetMinHitSize(48.0);
  EXPECT_DOUBLE_EQ(layout.GetMinHitSize(), 48.0);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, ExpandCenteredToMinGrowsPaint24ToHit44)
{
  // Roadmap 6.1: paint box 24×24 → hit AABB ≥ 44×44; paint geometry unchanged on the element.
  UI_BOUNDARYLINE paint;
  paint.x      = 100.0;
  paint.y      = 200.0;   // bottom-anchored
  paint.width  = 24.0;
  paint.height = 24.0;

  UI_BOUNDARYLINE hit = paint;
  hit.ExpandCenteredToMin(UI_LAYOUT_MINHITSIZE_DEFAULT, UI_LAYOUT_MINHITSIZE_DEFAULT);

  EXPECT_NEAR(hit.width,  44.0, 1e-9);
  EXPECT_NEAR(hit.height, 44.0, 1e-9);
  // Center preserved: mid_x = x + w/2, mid_y = y - h/2
  EXPECT_NEAR(hit.x + hit.width * 0.5,  paint.x + paint.width * 0.5, 1e-9);
  EXPECT_NEAR(hit.y - hit.height * 0.5, paint.y - paint.height * 0.5, 1e-9);

  // Point just outside paint, inside expanded hit
  EXPECT_FALSE(paint.IsWithin(99, 188));   // left of paint (paint left=100, top=176)
  EXPECT_TRUE(hit.IsWithin(99, 188));      // still inside hit (hit left=90, top=166)

  // Paint AABB itself was not mutated
  EXPECT_DOUBLE_EQ(paint.width,  24.0);
  EXPECT_DOUBLE_EQ(paint.height, 24.0);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, MinHitExpansionOnlyWhenUIScaleActive)
{
  // Same policy PreSelectElement applies: expand only if IsUIScaleActive && minhitsize > 0.
  UI_BOUNDARYLINE paint;
  paint.x = 50.0; paint.y = 80.0; paint.width = 24.0; paint.height = 24.0;

  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);
  layout.SetMinHitSize(44.0);

  UI_BOUNDARYLINE hit_off = paint;
  if(layout.IsUIScaleActive() && layout.GetMinHitSize() > 0.0)
    hit_off.ExpandCenteredToMin(layout.GetMinHitSize(), layout.GetMinHitSize());

  EXPECT_FALSE(layout.IsUIScaleActive());
  EXPECT_DOUBLE_EQ(hit_off.width,  24.0);
  EXPECT_DOUBLE_EQ(hit_off.height, 24.0);

  layout.SetUIScaleEnabled(true);

  UI_BOUNDARYLINE hit_on = paint;
  if(layout.IsUIScaleActive() && layout.GetMinHitSize() > 0.0)
    hit_on.ExpandCenteredToMin(layout.GetMinHitSize(), layout.GetMinHitSize());

  EXPECT_NEAR(hit_on.width,  44.0, 1e-9);
  EXPECT_NEAR(hit_on.height, 44.0, 1e-9);
}


TEST(UNITTESTS_UI_UISCALE_CLASSNAME, AssetRasterScaleTracksUIScaleWhenActive)
{
  // Fase 7: density is 1.0 when inactive; equals uiScale when UIScale is enabled.
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);
  layout.SetDesignSize(1440, 900);
  layout.SetUIScale(1.5);

  EXPECT_DOUBLE_EQ(layout.GetAssetRasterScale(), 1.0);

  layout.SetUIScaleEnabled(true);
  EXPECT_DOUBLE_EQ(layout.GetAssetRasterScale(), 1.5);

  layout.SetUIScale(2.0);
  EXPECT_DOUBLE_EQ(layout.GetAssetRasterScale(), 2.0);

  layout.SetUIScale(1.0);
  EXPECT_DOUBLE_EQ(layout.GetAssetRasterScale(), 1.0);
}


} // namespace TEST_UI_UISCALE
#endif // GOOGLETEST_ACTIVE
