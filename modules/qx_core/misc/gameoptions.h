#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H

namespace Qx
{


class GameOptions
{


    // Visual feedback

    /// Produce a short white flash on entities.
    /// When: Bullets hit enemy entities.
    inline static bool blinkImpact = true;

    /// Produce a screen yellow flash.
    /// When: Player shoots.
    inline static bool flashbang = true;

    /// Spawn a yellow halo particle.
    /// When: Player shoots or bullets hit anything.
    inline static bool lighting = true;

    /// Shake the camera horizontally or vertically.
    /// When: Player shoots (X shake) or lands from a high place (Y shake).
    inline static bool camShakesXY = true;

    /// Abruptly offset the camera for a short period of time.
    /// When: Player shoots or lands from a high place.
    inline static bool camBumpXY = true;

    /// Abruptly zoom-in the camera for a short period of time.
    /// When: Player lands or dashes.
    inline static bool camBumpZoom = true;


    // Squash and stretch

    /// Distort enemies like a jelly ball in reaction to external events.
    /// When: Enemies are hit by bullets.
    inline static bool mobSquashAndStrech = true;

    /// Distort the hero like a jelly ball in reaction to external events.
    /// When: Player jumps, lands, dashes or shoots.
    inline static bool heroSquashAndStrech = true;


    // Animations

    /// Slightly randomize bullet spreading to make them feel more natural.
    inline static bool randomizeBullets = true;

    /// Activate simple animations for the player.
    inline static bool basicAnimations = true;

    /// Activate weapon-related animations for the player.
    /// When: Player shoots.
    inline static bool gunAnimations = true;


    // Particles and effects

    /// Produce small cartridge particles that fall and bounce on the ground.
    inline static bool cartridges = true;

    /// Produce brief burst particles at the weapon muzzle.
    /// When: Player shoots.
    inline static bool gunShotFx = true;

    /// Add a short tail of light to bullets as they move.
    inline static bool bulletTail = true;

    /// Produce brief impact particles at the impact point.
    /// When: Bullets hit anything.
    inline static bool bulletImpactFx = true;

    /// Produce dust particles that fall to the ground at the impact point.
    /// When: Bullets hit anything.
    inline static bool bulletImpactDustFx = true;

    /// Produce particles on walls that fade from yellow to red.
    /// When: Bullets hit a wall.
    inline static bool bulletWallBurnFx = true;

    /// Produce blood particles on enemy impacts.
    /// When: Bullets hit enemies.
    inline static bool blood = true;

    /// Produce a small smoke puff when the player jumps or lands.
    inline static bool jumpFx = true;

    /// Produce blue light trail particles as the player dashes.
    /// When: Player dashes.
    inline static bool dashFx = true;


    // Recoil

    /// Slightly offset the player sprite without affecting physics.
    /// When: Player shoots.
    inline static bool gunRecoilVisual = true;

    /// Slightly move the player entity when shooting.
    /// When: Player shoots.
    inline static bool gunRecoilMovement = true;


    // Gameplay reactions

    /// Briefly lock player controls after intense events.
    /// When: Player lands from a high place.
    inline static bool controlLocks = true;

    /// Enable physical reactions for enemies.
    /// When: Enemies are hit by bullets or the player lands nearby.
    inline static bool enemyPhysicalReactions = true;


    // Entities

    /// Killing an enemy spawns a cadaver entity.
    inline static bool cadavers = true;


    // Traversal helpers

    /// Automatically jump small steps while walking.
    inline static bool smallStepsHelper = true;

    /// Automatically grab a cliff edge when barely missing it.
    inline static bool cliffGrabHelper = true;

    /// Spawn dust particles when traversal helpers activate.
    /// When: Player climbs a step or cliff.
    inline static bool climbFx = true;

    /// Allow the player to jump shortly after leaving the ground.
    inline static bool justInTimeJump = true;

    /// Queue player inputs while controls are temporarily locked.
    inline static bool ctrlQueue = true;

    /// Slow down the game briefly when the player dashes.
    inline static bool slowMos = true;


    // Rendering

    /// Render level textures.
    inline static bool levelTextures = true;

    /// Render the hero sprite and enabled animations.
    inline static bool heroSprite = true;


};

}


#endif // GAMEOPTIONS_H
