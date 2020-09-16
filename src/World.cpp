#include <Application.h>
#include <World.h>

World::World(const std::shared_ptr<Application> &app)
{
    m_context = std::make_shared<Context>();

    m_context->app = app;
    m_context->renderer = m_context->app->renderer();
    m_context->assetLoader = std::make_shared<AssetLoader>(m_context->renderer);
}

void World::drawLoadingBar(int x, int y, int w, int h, float percent, const SDL_Color &fgColor, const SDL_Color &bgColor)
{
    auto renderer = m_context->renderer->renderer();

    percent = percent > 1.f ? 1.f : percent < 0.f ? 0.f : percent;

    SDL_Color old;
    SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.g, &old.a);
    SDL_Rect bgrect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &bgrect);
    SDL_SetRenderDrawColor(renderer, fgColor.r, fgColor.g, fgColor.b, fgColor.a);
    int pw = (int)((float)w * percent);
    SDL_Rect fgrect = { x, y, pw, h };
    SDL_RenderFillRect(renderer, &fgrect);
    SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a); 
}

void World::drawLoadingScene()
{
    auto renderer = m_context->renderer->renderer();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    const unsigned int screenWidth = m_context->renderer->screenWidth();
    const unsigned int screenHeight = m_context->renderer->screenHeight();

    unsigned int barHeight = 32;

    unsigned int barX = 10;
    unsigned int barY = screenHeight - (barHeight + 10);

    unsigned int barWidth = screenWidth - (barX * 2);

    float percent = (float) m_context->assetLoader->loadedAssets() / (float) m_context->assetLoader->totalAssets();

    drawLoadingBar(barX, barY, barWidth, barHeight, percent, { 255, 255, 255, 255 }, { 0, 0, 0, 255 });
}