#pragma once

#include <Kismet/KismetSystemLibrary.h>
#include <Engine/EngineTypes.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include <Camera/CameraComponent.h>
#include "GeneralUtilityBPLibrary.generated.h"

UCLASS()
class GENERALUTILITY_API UGeneralUtilityBPLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:

    /**
     * Calculates the vertical field of view based on (the cameras) horizontal field of view and screen ratio,
     * caching this value might be worthwhile if needed often
     *
     * @param HorizontalFieldOfView   The horizontal field of view
     * @param ScreenRatio             The screen ratio in w/h value
     * @return                        The vertical field of view
     */
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Calculate Vertical Field Of View"), Category = "Camera")

    static float CalculateVerticalFoV(float HorizontalFieldOfView, float ScreenRatio) {
        return FMath::RadiansToDegrees(2.f * FMath::Atan(
                FMath::Tan(
                        FMath::DegreesToRadians(HorizontalFieldOfView) / 2.f
                ) * (1.f / ScreenRatio))
        );
    }

/**
 * Does a Sphere trace in a capsule shape and then limits returned items by a cone, writen to be similar
 * to {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 *
 * @param WorldContextObject        World context
 * @param Location                  Start location (e.g. camera)
 * @param Orientation               Which orientation the capsule should have (e.g. up  to down or left to right)
 * @param ViewRotation              Which angle the cone forms (e.g. camera's forward rotation)
 * @param Distance                  This distance from the {@code Location} in the @{code ViewRotation}'s that should be queried
 * @param HorizontalFieldOfView     The horizontal angle that objects should be found within
 * @param VerticalFieldOfView       The vertical angle that objects should be found within
 * @param ObjectTypes               Array of Object Types to trace
 * @param bTraceComplex             True to test against complex collision, false to test against simplified collision.
 * @param ActorsToIgnore
 * @param DrawDebugType
 * @param OutHits                   A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one
 * @param bIgnoreSelf
 * @param TraceColor                Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param TraceHitColor             Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param ScanColor                 Debug colour of actor tested that was not in cone
 * @param ActorColor                Debug colour of actor tested that was in cone
 * @param DrawTime                  How long the debug renders should stay active
 * @return                          True if there was a hit, false otherwise.
 */
    UFUNCTION(BlueprintCallable, Category = "Collision",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static bool
    ConeCapsuleTraceMultiForObject(UObject *WorldContextObject, FVector Location, FVector Orientation,
                                   FRotator ViewRotation, float Distance,
                                   float HorizontalFieldOfView, float VerticalFieldOfView,
                                   const TArray<TEnumAsByte<EObjectTypeQuery> > &ObjectTypes, bool bTraceComplex,
                                   const TArray<AActor *> &ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType,
                                   TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                   FLinearColor TraceColor = FLinearColor::Red,
                                   FLinearColor TraceHitColor = FLinearColor::Green,
                                   FLinearColor ScanColor = FLinearColor::Yellow,
                                   FLinearColor ActorColor = FLinearColor::Blue, float DrawTime = 5.0f);


/**
 * Does a Sphere trace in a capsule shape and then limits returned items by a cone, writen to be similar
 * to {@link UKismetSystemLibrary::SphereTraceMultiByChannel}
 *
 * @param WorldContextObject        World context
 * @param Location                  Start location (e.g. camera)
 * @param Orientation               Which orientation the capsule should have (e.g. up  to down or left to right)
 * @param ViewRotation              Which angle the cone forms (e.g. camera's forward rotation)
 * @param Distance                  This distance from the {@code Location} in the @{code ViewRotation}'s that should be queried
 * @param HorizontalFieldOfView     The horizontal angle that objects should be found within
 * @param VerticalFieldOfView       The vertical angle that objects should be found within
 * @param ProfileName               The 'profile' used to determine which components to hit
 * @param bTraceComplex             True to test against complex collision, false to test against simplified collision.
 * @param ActorsToIgnore
 * @param DrawDebugType
 * @param OutHits                   A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one
 * @param bIgnoreSelf
 * @param TraceColor                Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param TraceHitColor             Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param ScanColor                 Debug colour of actor tested that was not in cone
 * @param ActorColor                Debug colour of actor tested that was in cone
 * @param DrawTime                  How long the debug renders should stay active
 * @return                          True if there was a hit, false otherwise.
 */
    UFUNCTION(BlueprintCallable, Category = "Collision",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static bool
    ConeCapsuleTraceMultiByProfile(UObject *WorldContextObject, FVector Location, FVector Orientation,
                                   FRotator ViewRotation, float Distance,
                                   float HorizontalFieldOfView, float VerticalFieldOfView,
                                   FName ProfileName, bool bTraceComplex, const TArray<AActor *> &ActorsToIgnore,
                                   EDrawDebugTrace::Type DrawDebugType, TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                   FLinearColor TraceColor = FLinearColor::Red,
                                   FLinearColor TraceHitColor = FLinearColor::Green,
                                   FLinearColor ScanColor = FLinearColor::Yellow,
                                   FLinearColor ActorColor = FLinearColor::Blue, float DrawTime = 5.0f);

/**
 * Does a Sphere trace in a capsule shape and then limits returned items by a cone, writen to be similar
 * to {@link UKismetSystemLibrary::SphereTraceMulti}
 *
 * @param WorldContextObject        World context
 * @param Location                  Start location (e.g. camera)
 * @param Orientation               Which orientation the capsule should have (e.g. up  to down or left to right)
 * @param ViewRotation              Which angle the cone forms (e.g. camera's forward rotation)
 * @param Distance                  This distance from the {@code Location} in the @{code ViewRotation}'s that should be queried
 * @param HorizontalFieldOfView     The horizontal angle that objects should be found within
 * @param VerticalFieldOfView       The vertical angle that objects should be found within
 * @param TraceChannel
 * @param bTraceComplex             True to test against complex collision, false to test against simplified collision.
 * @param ActorsToIgnore
 * @param DrawDebugType
 * @param OutHits                   A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one
 * @param bIgnoreSelf
 * @param TraceColor                Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param TraceHitColor             Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param ScanColor                 Debug colour of actor tested that was not in cone
 * @param ActorColor                Debug colour of actor tested that was in cone
 * @param DrawTime                  How long the debug renders should stay active
 * @return                          True if there was a hit, false otherwise.
 */
    UFUNCTION(BlueprintCallable, Category = "Collision",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static bool
    ConeCapsuleTraceMultiByChannel(UObject *WorldContextObject, FVector Location, FVector Orientation,
                                   FRotator ViewRotation, float Distance,
                                   float HorizontalFieldOfView, float VerticalFieldOfView,
                                   ETraceTypeQuery TraceChannel, bool bTraceComplex,
                                   const TArray<AActor *> &ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType,
                                   TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                   FLinearColor TraceColor = FLinearColor::Red,
                                   FLinearColor TraceHitColor = FLinearColor::Green,
                                   FLinearColor ScanColor = FLinearColor::Yellow,
                                   FLinearColor ActorColor = FLinearColor::Blue, float DrawTime = 5.0f);

/**
 * Does a Sphere trace and then limits returned items by a cone, writen to be similar
 * to {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 *
 * @param WorldContextObject        World context
 * @param Location                  Start location (e.g. camera)
 * @param ViewRotation              Which angle the cone forms (e.g. camera's forward rotation)
 * @param Distance                  This distance from the {@code Location} in the @{code ViewRotation}'s that should be queried
 * @param HorizontalFieldOfView     The horizontal angle that objects should be found within
 * @param VerticalFieldOfView       The vertical angle that objects should be found within
 * @param ObjectTypes               Array of Object Types to trace
 * @param bTraceComplex             True to test against complex collision, false to test against simplified collision.
 * @param ActorsToIgnore
 * @param DrawDebugType
 * @param OutHits                   A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one
 * @param bIgnoreSelf
 * @param TraceColor                Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param TraceHitColor             Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param ScanColor                 Debug colour of actor tested that was not in cone
 * @param ActorColor                Debug colour of actor tested that was in cone
 * @param DrawTime                  How long the debug renders should stay active
 * @return                          True if there was a hit, false otherwise.
 */
    UFUNCTION(BlueprintCallable, Category = "Collision",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static bool
    ConeSphereTraceMultiForObject(UObject *WorldContextObject, FVector Location, FRotator ViewRotation, float Distance,
                                  float HorizontalFieldOfView, float VerticalFieldOfView,
                                  const TArray<TEnumAsByte<EObjectTypeQuery> > &ObjectTypes, bool bTraceComplex,
                                  const TArray<AActor *> &ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType,
                                  TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                  FLinearColor TraceColor = FLinearColor::Red,
                                  FLinearColor TraceHitColor = FLinearColor::Green,
                                  FLinearColor ScanColor = FLinearColor::Yellow,
                                  FLinearColor ActorColor = FLinearColor::Blue, float DrawTime = 5.0f);


/**
 * Does a Sphere trace and then limits returned items by a cone, writen to be similar
 * to {@link UKismetSystemLibrary::SphereTraceMultiByChannel}
 *
 * @param WorldContextObject        World context
 * @param Location                  Start location (e.g. camera)
 * @param ViewRotation              Which angle the cone forms (e.g. camera's forward rotation)
 * @param Distance                  This distance from the {@code Location} in the @{code ViewRotation}'s that should be queried
 * @param HorizontalFieldOfView     The horizontal angle that objects should be found within
 * @param VerticalFieldOfView       The vertical angle that objects should be found within
 * @param ProfileName               The 'profile' used to determine which components to hit
 * @param bTraceComplex             True to test against complex collision, false to test against simplified collision.
 * @param ActorsToIgnore
 * @param DrawDebugType
 * @param OutHits                   A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one
 * @param bIgnoreSelf
 * @param TraceColor                Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param TraceHitColor             Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param ScanColor                 Debug colour of actor tested that was not in cone
 * @param ActorColor                Debug colour of actor tested that was in cone
 * @param DrawTime                  How long the debug renders should stay active
 * @return                          True if there was a hit, false otherwise.
 */
    UFUNCTION(BlueprintCallable, Category = "Collision",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static bool
    ConeSphereTraceMultiByProfile(UObject *WorldContextObject, FVector Location, FRotator ViewRotation, float Distance,
                                  float HorizontalFieldOfView, float VerticalFieldOfView,
                                  FName ProfileName, bool bTraceComplex, const TArray<AActor *> &ActorsToIgnore,
                                  EDrawDebugTrace::Type DrawDebugType, TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                  FLinearColor TraceColor = FLinearColor::Red,
                                  FLinearColor TraceHitColor = FLinearColor::Green,
                                  FLinearColor ScanColor = FLinearColor::Yellow,
                                  FLinearColor ActorColor = FLinearColor::Blue, float DrawTime = 5.0f);

/**
 * Does a Sphere trace and then limits returned items by a cone, writen to be similar
 * to {@link UKismetSystemLibrary::SphereTraceMulti}
 *
 * @param WorldContextObject        World context
 * @param Location                  Start location (e.g. camera)
 * @param ViewRotation              Which angle the cone forms (e.g. camera's forward rotation)
 * @param Distance                  This distance from the {@code Location} in the @{code ViewRotation}'s that should be queried
 * @param HorizontalFieldOfView     The horizontal angle that objects should be found within
 * @param VerticalFieldOfView       The vertical angle that objects should be found within
 * @param TraceChannel
 * @param bTraceComplex             True to test against complex collision, false to test against simplified collision.
 * @param ActorsToIgnore
 * @param DrawDebugType
 * @param OutHits                   A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one
 * @param bIgnoreSelf
 * @param TraceColor                Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param TraceHitColor             Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param ScanColor                 Debug colour of actor tested that was not in cone
 * @param ActorColor                Debug colour of actor tested that was in cone
 * @param DrawTime                  How long the debug renders should stay active
 * @return                          True if there was a hit, false otherwise.
 */
    UFUNCTION(BlueprintCallable, Category = "Collision",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static bool
    ConeSphereTraceMultiByChannel(UObject *WorldContextObject, FVector Location, FRotator ViewRotation, float Distance,
                                  float HorizontalFieldOfView, float VerticalFieldOfView,
                                  ETraceTypeQuery TraceChannel, bool bTraceComplex,
                                  const TArray<AActor *> &ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType,
                                  TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                  FLinearColor TraceColor = FLinearColor::Red,
                                  FLinearColor TraceHitColor = FLinearColor::Green,
                                  FLinearColor ScanColor = FLinearColor::Yellow,
                                  FLinearColor ActorColor = FLinearColor::Blue, float DrawTime = 5.0f);

/**
 * Does a Sphere trace and then limits returned items by a cone, writen to be similar
 * to {@link UKismetSystemLibrary::BoxTraceMultiForObjects}
 *
 * @param WorldContextObject        World context
 * @param Location                  Start location (e.g. camera)
 * @param ViewRotation              Which angle the cone forms (e.g. camera's forward rotation)
 * @param Distance                  This distance from the {@code Location} in the @{code ViewRotation}'s that should be queried
 * @param HorizontalFieldOfView     The horizontal angle that objects should be found within
 * @param VerticalFieldOfView       The vertical angle that objects should be found within
 * @param ObjectTypes               Array of Object Types to trace
 * @param bTraceComplex             True to test against complex collision, false to test against simplified collision.
 * @param ActorsToIgnore
 * @param DrawDebugType
 * @param OutHits                   A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one
 * @param bIgnoreSelf
 * @param TraceColor                Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param TraceHitColor             Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param ScanColor                 Debug colour of actor tested that was not in cone
 * @param ActorColor                Debug colour of actor tested that was in cone
 * @param DrawTime                  How long the debug renders should stay active
 * @return                          True if there was a hit, false otherwise.
 */
    UFUNCTION(BlueprintCallable, Category = "Collision",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static bool
    ConeBoxTraceMultiForObject(UObject *WorldContextObject, FVector Location, FRotator ViewRotation, float Distance,
                               float HorizontalFieldOfView, float VerticalFieldOfView,
                               const TArray<TEnumAsByte<EObjectTypeQuery> > &ObjectTypes, bool bTraceComplex,
                               const TArray<AActor *> &ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType,
                               TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                               FLinearColor TraceColor = FLinearColor::Red,
                               FLinearColor TraceHitColor = FLinearColor::Green,
                               FLinearColor ScanColor = FLinearColor::Yellow,
                               FLinearColor ActorColor = FLinearColor::Blue, float DrawTime = 5.0f);


/**
 * Does a Box trace and then limits returned items by a cone, writen to be similar
 * to {@link UKismetSystemLibrary::BoxTraceMultiByChannel}
 *
 * @param WorldContextObject        World context
 * @param Location                  Start location (e.g. camera)
 * @param ViewRotation              Which angle the cone forms (e.g. camera's forward rotation)
 * @param Distance                  This distance from the {@code Location} in the @{code ViewRotation}'s that should be queried
 * @param HorizontalFieldOfView     The horizontal angle that objects should be found within
 * @param VerticalFieldOfView       The vertical angle that objects should be found within
 * @param ProfileName               The 'profile' used to determine which components to hit
 * @param bTraceComplex             True to test against complex collision, false to test against simplified collision.
 * @param ActorsToIgnore
 * @param DrawDebugType
 * @param OutHits                   A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one
 * @param bIgnoreSelf
 * @param TraceColor                Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param TraceHitColor             Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param ScanColor                 Debug colour of actor tested that was not in cone
 * @param ActorColor                Debug colour of actor tested that was in cone
 * @param DrawTime                  How long the debug renders should stay active
 * @return                          True if there was a hit, false otherwise.
 */
    UFUNCTION(BlueprintCallable, Category = "Collision",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static bool
    ConeBoxTraceMultiByProfile(UObject *WorldContextObject, FVector Location, FRotator ViewRotation, float Distance,
                               float HorizontalFieldOfView, float VerticalFieldOfView,
                               FName ProfileName, bool bTraceComplex, const TArray<AActor *> &ActorsToIgnore,
                               EDrawDebugTrace::Type DrawDebugType, TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                               FLinearColor TraceColor = FLinearColor::Red,
                               FLinearColor TraceHitColor = FLinearColor::Green,
                               FLinearColor ScanColor = FLinearColor::Yellow,
                               FLinearColor ActorColor = FLinearColor::Blue, float DrawTime = 5.0f);

/**
 * Does a Box trace and then limits returned items by a cone, writen to be similar
 * to {@link UKismetSystemLibrary::BoxTraceMulti}
 *
 * @param WorldContextObject        World context
 * @param Location                  Start location (e.g. camera)
 * @param ViewRotation              Which angle the cone forms (e.g. camera's forward rotation)
 * @param Distance                  This distance from the {@code Location} in the @{code ViewRotation}'s that should be queried
 * @param HorizontalFieldOfView     The horizontal angle that objects should be found within
 * @param VerticalFieldOfView       The vertical angle that objects should be found within
 * @param TraceChannel
 * @param bTraceComplex             True to test against complex collision, false to test against simplified collision.
 * @param ActorsToIgnore
 * @param DrawDebugType
 * @param OutHits                   A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one
 * @param bIgnoreSelf
 * @param TraceColor                Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param TraceHitColor             Debug colour of {@link UKismetSystemLibrary::SphereTraceMultiForObjects}
 * @param ScanColor                 Debug colour of actor tested that was not in cone
 * @param ActorColor                Debug colour of actor tested that was in cone
 * @param DrawTime                  How long the debug renders should stay active
 * @return                          True if there was a hit, false otherwise.
 */
    UFUNCTION(BlueprintCallable, Category = "Collision",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static bool
    ConeBoxTraceMultiByChannel(UObject *WorldContextObject, FVector Location, FRotator ViewRotation, float Distance,
                               float HorizontalFieldOfView, float VerticalFieldOfView,
                               ETraceTypeQuery TraceChannel, bool bTraceComplex,
                               const TArray<AActor *> &ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType,
                               TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                               FLinearColor TraceColor = FLinearColor::Red,
                               FLinearColor TraceHitColor = FLinearColor::Green,
                               FLinearColor ScanColor = FLinearColor::Yellow,
                               FLinearColor ActorColor = FLinearColor::Blue, float DrawTime = 5.0f);


    /**
     * Removes items not in the code from the supplied array
     *
     * @param WorldContextObject    World context
     * @param Location              Start location (e.g. camera)
     * @param LeftAngle             The left angle of the code to check
     * @param RightAngle            The right angle of the code to check
     * @param TopAngle              The top angle of the code to check
     * @param BottomAngle           The bottom angle of the code to check
     * @param OutHits               The list to have items removed from
     * @param DrawDebugType
     * @param ScanColor             Debug colour of actor tested that was not in cone
     * @param ActorColor            Debug colour of actor tested that was in cone
     * @param DrawTime              How long the debug renders should stay active
     */
    UFUNCTION(BlueprintCallable, Category = "Filtering",
              meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,ScanColor,ActorColor,DrawTime", Keywords = "sweep"))

    static void
    FilterItemsIntoCone(UObject *WorldContextObject, FVector Location, float LeftAngle, float RightAngle,
                        float TopAngle, float BottomAngle, TArray<FHitResult> &OutHits,
                        EDrawDebugTrace::Type DrawDebugType, FLinearColor ActorColor = FLinearColor::Blue,
                        FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 5.f);


    /**
     * Similar to {@link UKismetSystemLibrary::DrawDebugCamera} but uses a component instead of an actor
     *
     * @param CameraActor
     * @param CameraColor
     * @param Duration
     */
    UFUNCTION(BlueprintCallable, Category = "Rendering|Debug", meta = (DevelopmentOnly))

    static void
    DrawDebugCameraComponent(const UCameraComponent *CameraActor, FLinearColor CameraColor = FLinearColor::White,
                             float Duration = 0.f);


};
